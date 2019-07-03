//
// Created by sziraqui on 22/6/19.
//

#ifndef NODOFACE_MATINT_H
#define NODOFACE_MATINT_H

#include "MatImage.h"

namespace Nodoface {
    // Wraps OpenCV Mat_<int> partially for sending and receiving Mat_<int> objects to/from node
    typedef MatImage<int> IntImage;
}



#endif //NODOFACE_MATINT_H
