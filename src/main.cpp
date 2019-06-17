#include <napi.h>
#include "io/ImageCapture.h"
#include "io/SequenceCapture.h"
#include "io/OutputUtils.h"
#include "cvtypes/Mat.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    Nodoface::ImageCapture::Init(env, exports);
    Nodoface::SequenceCapture::Init(env, exports);
    Nodoface::Image::Init(env, exports);
    Nodoface::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)