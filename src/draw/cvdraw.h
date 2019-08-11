//
// Created by sziraqui on 21/6/19.
//

#ifndef NODOFACE_CVDRAW_H
#define NODOFACE_CVDRAW_H

#include <vector>
#include <opencv2/opencv.hpp>

#include <napi.h>

#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"
#include "../cvtypes/Mat.h"

namespace Nodoface {
        
    namespace Draw {

        Napi::Object Init(Napi::Env env, Napi::Object exports);

        Napi::Value rectangle(const Napi::CallbackInfo& info);

//        Napi::Value circle(const Napi::CallbackInfo& info);
//
        Napi::Value putText(const Napi::CallbackInfo& info);
//
//        Napi::Value line(const Napi::CallbackInfo& info);
        
        Napi::Value drawDetections(const Napi::CallbackInfo& info);
    }
}

#endif //NODOFACE_CVDRAW_H
