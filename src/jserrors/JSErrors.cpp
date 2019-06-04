//
// Created by sziraqui on 4/6/19.
//
#include "JSErrors.h"

Napi::TypeError JSErrors::SetterError(Napi::Env env, std::string jsTypeName) {
    std::string msg = "Expected exactly 1 argument of type " + jsTypeName;
    return Napi::TypeError::New(env, msg).ThrowAsJavaScriptException();
}