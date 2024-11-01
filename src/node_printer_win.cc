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

MY_NODE_MODULE_CALLBACK(getPrinters) 
{
  MY_NODE_MODULE_HANDLESCOPE

  MY_NODE_MODULE_RETURN_VALUE(Napi::String::New(MY_NODE_MODULE_ENV, "native getPrinters Invoked"));
}

