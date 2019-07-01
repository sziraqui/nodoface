//
// Created by sziraqui on 16/6/19.
//

#ifndef NODOFACE_OUTPUTUTILS_H
#define NODOFACE_OUTPUTUTILS_H

#include <opencv2/opencv.hpp>

#include <napi.h>

#include "../cvtypes/Mat.h"

namespace Nodoface {
    namespace OutputUtils {
        Napi::Object Init(Napi::Env env, Napi::Object exports);

        Napi::Value showImage(const Napi::CallbackInfo &info);

        Napi::Value readImage(const Napi::CallbackInfo &info);

        Napi::Value destroyWindow(const Napi::CallbackInfo &info);

        Napi::Value destroyAllWindows(const Napi::CallbackInfo &info);

        Napi::Value waitKey(const Napi::CallbackInfo &info);

        Napi::Value saveImage(const Napi::CallbackInfo &info);
    }
    

}

#endif //NODOFACE_OUTPUTUTILS_H
