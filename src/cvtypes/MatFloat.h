//
// Created by sziraqui on 22/6/19.
//

#ifndef NODOFACE_MATFLOAT_H
#define NODOFACE_MATFLOAT_H

#include <vector>

#include <opencv2/core/mat.hpp>

#include <napi.h>

#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"
#include "MatImage.h"

namespace Nodoface {
    // Wraps OpenCV Mat_<float> partially for sending and receiving Mat_<float> objects to/from node
    class FloatImage : public Nodoface::MatImage<float> {

    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
    };
}

#endif //NODOFACE_MATFLOAT_H
