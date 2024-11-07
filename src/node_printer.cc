#include "node_printer.hpp"



Napi::Object Init(Napi::Env env, Napi::Object exports) {
  MY_MODULE_SET_METHOD(exports, "SayMyName", SayMyName);
  MY_MODULE_SET_METHOD(exports,"getPrinters", getPrinters);
  return exports;
}

NODE_API_MODULE(addon, Init)
