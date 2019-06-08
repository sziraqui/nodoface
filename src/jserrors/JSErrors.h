//
// Created by sziraqui on 4/6/19.
//

#ifndef NODOFACE_JSERRORS_H
#define NODOFACE_JSERRORS_H
#include <napi.h>
#include <string>

namespace JSErrors {

    const std::string NUMBER = "Number";
    const std::string STRING = "String";
    const std::string ARRAY = "Array";
    const std::string BOOLEAN = "Boolean";
    const std::string UINT8ARRAY = "Uint8Array";
    const std::string NONE = "NULL";

    void SetterError(Napi::Env env, std::string jsTypeName);
    void InsufficientArguments(Napi::Env, uint expectedArgLen, uint receivedArgLen);
    void TooManyArguments(Napi::Env env, uint expectedArgLen, uint receivedArgLen);
    void IncorrectDatatype(Napi::Env env, std::string expectedType, int argNum = 0);
}
#endif //NODOFACE_JSERRORS_H
