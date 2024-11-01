#ifndef NODE_PRINTER_SRC_MACROS_H
#define NODE_PRINTER_SRC_MACROS_H
#include <napi.h>


#define MY_NODE_MODULE_ENV_DECL Napi::Env env = info.Env();
#define MY_NODE_MODULE_ENV      env
#define MY_NODE_MODULE_HANDLESCOPE MY_NODE_MODULE_ENV_DECL Napi::HandleScope scope(env);

#define MY_MODULE_SET_METHOD(exports, name, method) \
    (exports).Set(Napi::String::New(env, name), Napi::Function::New(env, method))

#define MY_NODE_MODULE_CALLBACK(name) Napi::Value name(const Napi::CallbackInfo& info)

#define MY_NODE_MODULE_RETURN_VALUE(value) \
    return value;

#define NAPI_VALUE_NEW_DEFAULT(type, ...) Napi::type::New(MY_NODE_MODULE_ENV, __VA_ARGS__)


#endif

