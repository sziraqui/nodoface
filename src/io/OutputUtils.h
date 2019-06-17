//
// Created by sziraqui on 16/6/19.
//

#ifndef NODOFACE_OUTPUTUTILS_H
#define NODOFACE_OUTPUTUTILS_H

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


#include <napi.h>

#include "../extras/ndarray.h"

namespace Nodoface {

    Napi::Object Init(Napi::Env env, Napi::Object exports);

    Napi::Value showImage(const Napi::CallbackInfo &info);
}
#endif //NODOFACE_OUTPUTUTILS_H
