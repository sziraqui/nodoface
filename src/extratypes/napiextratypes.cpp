//
// Created by sziraqui on 4/6/19.
//
#include "napiextratypes.h"

std::vector<std::string> NapiExtra::StringArray::ToVector() {
    std::vector<std::string> vectStr(this->ElementLength());
    for(int i = 0; i < this->ElementLength(); ++i) {
        vectStr[i] = this[i].ToString().Utf8Value();
    }
    return vectStr;
}
