#include "node_printer.hpp"

using namespace Napi;

MY_NODE_MODULE_CALLBACK(SayMyName) 
{
  MY_NODE_MODULE_HANDLESCOPE

  MY_NODE_MODULE_RETURN_VALUE(String::New(MY_NODE_MODULE_ENV, "Electron printer"));
}