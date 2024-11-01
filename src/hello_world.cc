#include <napi.h>

using namespace Napi;

String SayMyName(const CallbackInfo& info) {
  Env env = info.Env();

  return String::New(env, "Electron printer");
}

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "SayMyName"), Function::New(env, SayMyName));
  return exports;
}

NODE_API_MODULE(addon, Init)
