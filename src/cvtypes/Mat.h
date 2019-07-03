//
// Created by sziraqui on 17/6/19.
//

#ifndef NODOFACE_MAT_H
#define NODOFACE_MAT_H

#include <vector>

#include <opencv2/core/mat.hpp>

#include <napi.h>

#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"
#include "MatImage.h"

namespace Nodoface {
    // Wraps OpenCV Mat partially for sending and receiving Mat objects to/from node
    class Image : public Nodoface::MatImage<uchar> {

        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
    };
}

#endif //NODOFACE_MAT_H
