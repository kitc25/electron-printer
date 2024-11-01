#include "node_printer.hpp"

using namespace Napi;

Object Init(Env env, Object exports) {
  MY_MODULE_SET_METHOD(exports, "SayMyName", SayMyName);
  return exports;
}

NODE_API_MODULE(addon, Init)