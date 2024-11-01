#ifndef NODE_PRINTER_SRC_MACROS_H
#define NODE_PRINTER_SRC_MACROS_H
#include <napi.h>

#define MY_MODULE_SET_METHOD(exports, name, method) \
    (exports).Set(Napi::String::New(env, name), Napi::Function::New(env, method))

#define MY_NODE_MODULE_CALLBACK(name) Napi::String name(const Napi::CallbackInfo& iArgs)

#endif

