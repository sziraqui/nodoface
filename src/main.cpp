#include <napi.h>
#include "io/ImageCapture.h"
#include "io/SequenceCapture.h"
#include "io/OutputUtils.h"
#include "cvtypes/Mat.h"
#include "facedetection/FaceDetectorMTCNN.h"
#include "draw/cvdraw.h"
#include "landmarkdetection/FaceModelParameters.h"
#include "cvtypes/MatFloat.h"
#include "cvtypes/MatInt.h"
#include "landmarkdetection/CLNF.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    Nodoface::ImageCapture::Init(env, exports);
    Nodoface::SequenceCapture::Init(env, exports);
    Nodoface::Image::Init(env, exports);
    Nodoface::FloatImage::Init(env, exports);
    Nodoface::IntImage::Init(env, exports);
    Nodoface::Init(env, exports);
    Nodoface::FaceDetectorMTCNN::Init(env, exports);
    Nodoface::Draw::Init(env, exports);
    Nodoface::LandmarkModelConfig::Init(env, exports);
    Nodoface::CLNF::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)