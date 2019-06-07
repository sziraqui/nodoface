//
// Created by sziraqui on 4/6/19.
//

#ifndef NODOFACE_NAPIEXTRATYPES_H
#define NODOFACE_NAPIEXTRATYPES_H
#include <napi.h>
#include <vector>
#include <string>
namespace NapiExtra {

    class StringArray : public Napi::TypedArrayOf<Napi::String> {
        std::vector<std::string> ToVector();
    };
}
#endif //NODOFACE_NAPIEXTRATYPES_H
