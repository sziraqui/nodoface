//
// Created by sziraqui on 4/6/19.
//
#include "JSErrors.h"

void JSErrors::SetterError(Napi::Env env, std::string jsTypeName) {
    std::string msg = "Expected exactly 1 argument of type " + jsTypeName;
    Napi::TypeError::New(env, msg).ThrowAsJavaScriptException();
}

void JSErrors::TooManyArguments(Napi::Env env, uint expectedArgLen, uint receivedArgLen) {
    std::string msg = "Expected " + std::to_string(expectedArgLen) + " args(s) but got " + std::to_string(receivedArgLen) + " args(s)";
    Napi::Error::New(env, msg).ThrowAsJavaScriptException();
}