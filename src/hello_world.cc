#include "node_printer.hpp"

using namespace Napi;

MY_NODE_MODULE_CALLBACK(SayMyName) 
{
  Env env = iArgs.Env();
  return String::New(env, "Electron printer");
}

Object Init(Env env, Object exports) {
  MY_MODULE_SET_METHOD(exports, "SayMyName", SayMyName);
  return exports;
}

NODE_API_MODULE(addon, Init)
