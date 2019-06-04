//
// Created by sziraqui on 4/6/19.
//

#ifndef NODOFACE_JSERRORS_H
#define NODOFACE_JSERRORS_H
#include <napi.h>

namespace JSErrors {

    const std::string NUMBER = "Number";
    const std::string BOOLEAN = "Boolean";
    const std::string UINT8ARRAY = "Uint8Array";

    Napi::TypeError SetterError(Napi::Env env, std::string jsTypeName);

}
#endif //NODOFACE_JSERRORS_H
