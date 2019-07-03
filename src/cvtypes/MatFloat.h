//
// Created by sziraqui on 22/6/19.
//

#ifndef NODOFACE_MATFLOAT_H
#define NODOFACE_MATFLOAT_H

#include "MatImage.h"

namespace Nodoface {
    // Wraps OpenCV Mat_<float> partially for sending and receiving Mat_<float> objects to/from node
    typedef MatImage<float> FloatImage;
}

#endif //NODOFACE_MATFLOAT_H
