#include "node_printer.hpp"

using namespace Napi;

MY_NODE_MODULE_CALLBACK(SayMyName) 
{
  Env env = iArgs.Env();
  return String::New(env, "Electron printer");
}