//
// Created by sziraqui on 17/6/19.
//

#ifndef NODOFACE_MAT_H
#define NODOFACE_MAT_H

#include "MatImage.h"

namespace Nodoface {
    // Wraps OpenCV Mat partially for sending and receiving Mat objects to/from node
    typedef MatImage<uchar> Image;
}

#endif //NODOFACE_MAT_H
