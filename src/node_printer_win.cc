#include "node_printer.hpp"
#if _MSC_VER
#include <windows.h>
#include <Winspool.h>
#include <Wingdi.h>
#pragma  comment(lib, "Winspool.lib")
#else
#error "Unsupported compiler for windows. Feel free to add it."
#endif

#include <string>
#include <map>
#include <utility>
#include <sstream>
#include <cstdio>

// Utility function to output messages
void ConsolePrint(const std::string& message) {
    printf("%s\n", message.c_str());
    fflush(stdout); // Ensure the output is flushed immediately
}

namespace{
    typedef std::map<std::string, DWORD> StatusMapType;

    /** Memory value class management to avoid memory leak
    */
    template<typename Type>
    class MemValue: public MemValueBase<Type> {
    public:
        /** Constructor of allocating iSizeKbytes bytes memory;
        * @param iSizeKbytes size in bytes of required allocating memory
        */
        MemValue(const DWORD iSizeKbytes) {
            _value = (Type*)malloc(iSizeKbytes);
        }
		
        ~MemValue () {
            free();
        }

        Type* get() {
        return _value;
        }
    protected:
        virtual void free() {
            if(_value != NULL)
            {
                ::free(_value);
                _value = NULL;
            }
        }

    private:
    Type* _value; // Declaration of the member variable
    };

        struct PrinterHandle
    {
        PrinterHandle(LPWSTR iPrinterName)
        {
            _ok = OpenPrinterW(iPrinterName, &_printer, NULL);
        }
        ~PrinterHandle()
        {
            if(_ok)
            {
                ClosePrinter(_printer);
            }
        }
        operator HANDLE() {return _printer;}
        operator bool() { return (!!_ok);}
        HANDLE & operator *() { return _printer;}
        HANDLE * operator ->() { return &_printer;}
        const HANDLE & operator ->() const { return _printer;}
        HANDLE _printer;
        BOOL _ok;
    };

    const StatusMapType& getStatusMap()
    {
        static StatusMapType result;
        if(!result.empty())
        {
            return result;
        }
        // add only first time
#define STATUS_PRINTER_ADD(value, type) result.insert(std::make_pair(value, type))
        STATUS_PRINTER_ADD("BUSY", PRINTER_STATUS_BUSY);
        STATUS_PRINTER_ADD("DOOR-OPEN", PRINTER_STATUS_DOOR_OPEN);
        STATUS_PRINTER_ADD("ERROR", PRINTER_STATUS_ERROR);
        STATUS_PRINTER_ADD("INITIALIZING", PRINTER_STATUS_INITIALIZING);
        STATUS_PRINTER_ADD("IO-ACTIVE", PRINTER_STATUS_IO_ACTIVE);
        STATUS_PRINTER_ADD("MANUAL-FEED", PRINTER_STATUS_MANUAL_FEED);
        STATUS_PRINTER_ADD("NO-TONER", PRINTER_STATUS_NO_TONER);
        STATUS_PRINTER_ADD("NOT-AVAILABLE", PRINTER_STATUS_NOT_AVAILABLE);
        STATUS_PRINTER_ADD("OFFLINE", PRINTER_STATUS_OFFLINE);
        STATUS_PRINTER_ADD("OUT-OF-MEMORY", PRINTER_STATUS_OUT_OF_MEMORY);
        STATUS_PRINTER_ADD("OUTPUT-BIN-FULL", PRINTER_STATUS_OUTPUT_BIN_FULL);
        STATUS_PRINTER_ADD("PAGE-PUNT", PRINTER_STATUS_PAGE_PUNT);
        STATUS_PRINTER_ADD("PAPER-JAM", PRINTER_STATUS_PAPER_JAM);
        STATUS_PRINTER_ADD("PAPER-OUT", PRINTER_STATUS_PAPER_OUT);
        STATUS_PRINTER_ADD("PAPER-PROBLEM", PRINTER_STATUS_PAPER_PROBLEM);
        STATUS_PRINTER_ADD("PAUSED", PRINTER_STATUS_PAUSED);
        STATUS_PRINTER_ADD("PENDING-DELETION", PRINTER_STATUS_PENDING_DELETION);
        STATUS_PRINTER_ADD("POWER-SAVE", PRINTER_STATUS_POWER_SAVE);
        STATUS_PRINTER_ADD("PRINTING", PRINTER_STATUS_PRINTING);
        STATUS_PRINTER_ADD("PROCESSING", PRINTER_STATUS_PROCESSING);
        STATUS_PRINTER_ADD("SERVER-UNKNOWN", PRINTER_STATUS_SERVER_UNKNOWN);
        STATUS_PRINTER_ADD("TONER-LOW", PRINTER_STATUS_TONER_LOW);
        STATUS_PRINTER_ADD("USER-INTERVENTION", PRINTER_STATUS_USER_INTERVENTION);
        STATUS_PRINTER_ADD("WAITING", PRINTER_STATUS_WAITING);
        STATUS_PRINTER_ADD("WARMING-UP", PRINTER_STATUS_WARMING_UP);
#undef STATUS_PRINTER_ADD
        return result;
    }

    const StatusMapType& getJobStatusMap()
    {
        static StatusMapType result;
        if(!result.empty())
        {
            return result;
        }
        // add only first time
#define STATUS_PRINTER_ADD(value, type) result.insert(std::make_pair(value, type))
        // Common statuses
        STATUS_PRINTER_ADD("PRINTING", JOB_STATUS_PRINTING);
        STATUS_PRINTER_ADD("PRINTED", JOB_STATUS_PRINTED);
        STATUS_PRINTER_ADD("PAUSED", JOB_STATUS_PAUSED);

        // Specific statuses
        STATUS_PRINTER_ADD("BLOCKED-DEVQ", JOB_STATUS_BLOCKED_DEVQ);
        STATUS_PRINTER_ADD("DELETED", JOB_STATUS_DELETED);
        STATUS_PRINTER_ADD("DELETING", JOB_STATUS_DELETING);
        STATUS_PRINTER_ADD("ERROR", JOB_STATUS_ERROR);
        STATUS_PRINTER_ADD("OFFLINE", JOB_STATUS_OFFLINE);
        STATUS_PRINTER_ADD("PAPEROUT", JOB_STATUS_PAPEROUT);
        STATUS_PRINTER_ADD("RESTART", JOB_STATUS_RESTART);
        STATUS_PRINTER_ADD("SPOOLING", JOB_STATUS_SPOOLING);
        STATUS_PRINTER_ADD("USER-INTERVENTION", JOB_STATUS_USER_INTERVENTION);
        // XP and later
#ifdef JOB_STATUS_COMPLETE
        STATUS_PRINTER_ADD("COMPLETE", JOB_STATUS_COMPLETE);
#endif
#ifdef JOB_STATUS_RETAINED
        STATUS_PRINTER_ADD("RETAINED", JOB_STATUS_RETAINED);
#endif

#undef STATUS_PRINTER_ADD
        return result;
    }

    const StatusMapType& getAttributeMap()
    {
        static StatusMapType result;
        if(!result.empty())
        {
            return result;
        }
        // add only first time
#define ATTRIBUTE_PRINTER_ADD(value, type) result.insert(std::make_pair(value, type))
        ATTRIBUTE_PRINTER_ADD("DIRECT", PRINTER_ATTRIBUTE_DIRECT);
        ATTRIBUTE_PRINTER_ADD("DO-COMPLETE-FIRST", PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST);
        ATTRIBUTE_PRINTER_ADD("ENABLE-DEVQ", PRINTER_ATTRIBUTE_ENABLE_DEVQ);
        ATTRIBUTE_PRINTER_ADD("HIDDEN", PRINTER_ATTRIBUTE_HIDDEN);
        ATTRIBUTE_PRINTER_ADD("KEEPPRINTEDJOBS", PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS);
        ATTRIBUTE_PRINTER_ADD("LOCAL", PRINTER_ATTRIBUTE_LOCAL);
        ATTRIBUTE_PRINTER_ADD("NETWORK", PRINTER_ATTRIBUTE_NETWORK);
        ATTRIBUTE_PRINTER_ADD("PUBLISHED", PRINTER_ATTRIBUTE_PUBLISHED);
        ATTRIBUTE_PRINTER_ADD("QUEUED", PRINTER_ATTRIBUTE_QUEUED);
        ATTRIBUTE_PRINTER_ADD("RAW-ONLY", PRINTER_ATTRIBUTE_RAW_ONLY);
        ATTRIBUTE_PRINTER_ADD("SHARED", PRINTER_ATTRIBUTE_SHARED);
        ATTRIBUTE_PRINTER_ADD("OFFLINE", PRINTER_ATTRIBUTE_WORK_OFFLINE);
        // XP
#ifdef PRINTER_ATTRIBUTE_FAX
        ATTRIBUTE_PRINTER_ADD("FAX", PRINTER_ATTRIBUTE_FAX);
#endif
        // vista
#ifdef PRINTER_ATTRIBUTE_FRIENDLY_NAME
        ATTRIBUTE_PRINTER_ADD("FRIENDLY-NAME", PRINTER_ATTRIBUTE_FRIENDLY_NAME);
        ATTRIBUTE_PRINTER_ADD("MACHINE", PRINTER_ATTRIBUTE_MACHINE);
        ATTRIBUTE_PRINTER_ADD("PUSHED-USER", PRINTER_ATTRIBUTE_PUSHED_USER);
        ATTRIBUTE_PRINTER_ADD("PUSHED-MACHINE", PRINTER_ATTRIBUTE_PUSHED_MACHINE);
#endif
        // server 2003
#ifdef PRINTER_ATTRIBUTE_TS
        ATTRIBUTE_PRINTER_ADD("TS", PRINTER_ATTRIBUTE_TS);
#endif
#undef ATTRIBUTE_PRINTER_ADD
        return result;
    }

    const StatusMapType& getJobCommandMap()
    {
        static StatusMapType result;
        if(!result.empty())
        {
            return result;
        }
        // add only first time
#define COMMAND_JOB_ADD(value, type) result.insert(std::make_pair(value, type))
        COMMAND_JOB_ADD("CANCEL", JOB_CONTROL_CANCEL);
        COMMAND_JOB_ADD("PAUSE", JOB_CONTROL_PAUSE);
        COMMAND_JOB_ADD("RESTART", JOB_CONTROL_RESTART);
        COMMAND_JOB_ADD("RESUME", JOB_CONTROL_RESUME);
        COMMAND_JOB_ADD("DELETE", JOB_CONTROL_DELETE);
        COMMAND_JOB_ADD("SENT-TO-PRINTER", JOB_CONTROL_SENT_TO_PRINTER);
        COMMAND_JOB_ADD("LAST-PAGE-EJECTED", JOB_CONTROL_LAST_PAGE_EJECTED);
#ifdef JOB_CONTROL_RETAIN
        COMMAND_JOB_ADD("RETAIN", JOB_CONTROL_RETAIN);
#endif
#ifdef JOB_CONTROL_RELEASE
        COMMAND_JOB_ADD("RELEASE", JOB_CONTROL_RELEASE);
#endif
#undef COMMAND_JOB_ADD
        return result;
    }

}

MY_NODE_MODULE_CALLBACK(getPrinters) 
{
  MY_NODE_MODULE_HANDLESCOPE

  MY_NODE_MODULE_RETURN_VALUE(Napi::String::New(MY_NODE_MODULE_ENV, "native getPrinters Invoked"));
}

