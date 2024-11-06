#ifndef NODE_PRINTER_SRC_MACROS_H
#define NODE_PRINTER_SRC_MACROS_H
#include <napi.h>


#define MY_NODE_MODULE_ENV_DECL Napi::Env env = info.Env();
#define MY_NODE_MODULE_ENV      env
#define MY_NODE_MODULE_HANDLESCOPE MY_NODE_MODULE_ENV_DECL Napi::HandleScope scope(env);

#define MY_MODULE_SET_METHOD(exports, name, method) \
    (exports).Set(Napi::String::New(env, name), Napi::Function::New(env, method))

#define MY_NODE_MODULE_CALLBACK(name) void name(const Napi::CallbackInfo& info)

#define MY_NODE_MODULE_RETURN_VALUE(value) \
    return value;

#define NAPI_STRING_NEW_UTF8(env, value) Napi::String::New(env, value)

#define ADD_NAPI_NUMBER_PROPERTY(obj, name, value) \
    obj.Set(Napi::String::New(obj.Env(), name), Napi::Number::New(obj.Env(), value))

#define NAPI_STRING_NEW_2BYTES(env, value) Napi::String::New(env, (char16_t*)value)

#define ADD_NAPI_STRING_PROPERTY(obj, name, key) \
if ((job->key != NULL) && (*job->key != L'\0')) { \
    obj.Set(Napi::String::New(obj.Env(), name), Napi::String::New(obj.Env(), (char16_t*)job->key)); \
}





#endif

