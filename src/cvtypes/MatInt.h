//
// Created by sziraqui on 22/6/19.
//

#ifndef NODOFACE_MATINT_H
#define NODOFACE_MATINT_H

#include <vector>

#include <opencv2/core/mat.hpp>

#include <napi.h>

#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"
#include "MatImage.h"

namespace Nodoface {
    // Wraps OpenCV Mat_<int> partially for sending and receiving Mat_<int> objects to/from node
    class IntImage : public Nodoface::MatImage<float> {

    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
    };
}



#endif //NODOFACE_MATINT_H
