#include <napi.h>

using namespace Napi;

Napi::String SayMyName(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  return Napi::String::New(env, "Electron printer");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "SayMyName"), Napi::Function::New(env, SayMyName));
  return exports;
}

NODE_API_MODULE(addon, Init)
