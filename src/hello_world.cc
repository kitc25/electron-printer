#include "node_printer.hpp"

MY_NODE_MODULE_CALLBACK(SayMyName) 
{
  MY_NODE_MODULE_HANDLESCOPE

  MY_NODE_MODULE_RETURN_VALUE(Napi::String::New(MY_NODE_MODULE_ENV, "Electron printer test"));
}