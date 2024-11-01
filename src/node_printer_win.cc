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
}

MY_NODE_MODULE_CALLBACK(getPrinters) 
{
  MY_NODE_MODULE_HANDLESCOPE

  MY_NODE_MODULE_RETURN_VALUE(Napi::String::New(MY_NODE_MODULE_ENV, "native getPrinters Invoked"));
}

