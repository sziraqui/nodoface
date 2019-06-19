//
// Created by sziraqui on 17/6/19.
//

#include "Mat.h"
#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"

Napi::FunctionReference Nodoface::Image::constructor;

// static methods
Napi::Object Nodoface::Image::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Image", {
        InstanceMethod("type", &Nodoface::Image::Type),
        InstanceMethod("height", &Nodoface::Image::Rows),
        InstanceMethod("width", &Nodoface::Image::Columns),
        InstanceMethod("channels", &Nodoface::Image::Channels)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Image", func);
    return exports;
}

Napi::Value Nodoface::Image::NewObject(Napi::Env env, cv::Mat* mat) {
    Napi::EscapableHandleScope scope(env);
    // Get continuous mat data
    uchar* data;
    size_t length = mat->total() * mat->channels();
    if(mat->isContinuous()) {
        mat = new cv::Mat(*mat); // ensures mat is continuous and also prevents segfault
    }
    data = mat->data;

    // Create ArrayBuffer from data
    Napi::ArrayBuffer ab = Napi::ArrayBuffer::New(env, data, sizeof(uchar)*length);
    Napi::TypedArrayOf<uchar> arr = Napi::TypedArrayOf<uchar>::New(env, length, ab, 0); // arg1
    // Mat dimensions
    Napi::Number rows = Napi::Number::New(env, mat->rows); // arg2
    Napi::Number cols = Napi::Number::New(env, mat->cols); // arg3
    // Create mat type Number
    Napi::Number type = Napi::Number::New(env, mat->type());  // arg4
    // Call constructor
    Napi::Object imageObj = Image::constructor.New({ arr, rows, cols, type });
#ifdef DEBUG_MATWRAPPER
    Image* image = Napi::ObjectWrap<Image>::Unwrap(imageObj);
    cv::namedWindow("NewObject", cv::WINDOW_AUTOSIZE);
    cv::imshow("NewObject", image->GetMat());
    cv::waitKey(0);
#endif
    return scope.Escape(imageObj);
}
// cpp only
cv::Mat* Nodoface::Image::NewMat(Napi::TypedArrayOf<uchar> &arr, Napi::Number& rows, Napi::Number& cols, Napi::Number& type) {
    // Get mat data
    auto buf = arr.ArrayBuffer();
    uchar* data = reinterpret_cast<uchar *>(buf.Data()); // reinterpret_cast for void* to uchar*
    // Get mat size
    size_t matRows = rows.Int32Value();
    size_t matCols = cols.Int32Value();
    // Get Mat type
    int matType = type.Int32Value();
    // Create mat
    cv::Mat* mat = new cv::Mat(matRows, matCols, matType, data);
#ifdef DEBUG_MATWRAPPER
    cv::namedWindow("NewMat", cv::WINDOW_AUTOSIZE);
    cv::imshow("NewMat", mat);
    cv::waitKey(0);
#endif
    return mat;
}

// constructor
Nodoface::Image::Image(const Napi::CallbackInfo& info) : ObjectWrap<Nodoface::Image>(info) {
    int len = info.Length();
    auto env = info.Env();
    if(len == 0 || len == 2) {
        JSErrors::InsufficientArguments(env, 4, 0);
    } else if (len == 1 && info[0].IsObject()) {
        // copy constructor
        Image * img = Napi::ObjectWrap<Nodoface::Image>::Unwrap(info[1].As<Napi::Object>());
        this->mat = img->mat;
    } else if (len == 4) {
        // constructor with data as arrays
        if(!info[0].IsTypedArray()) {
            JSErrors::IncorrectDatatype(env, JSErrors::TYPEDARRAY, 1);
        }
        for (int i = 1; i <= 3 && !info[i].IsNumber(); i++) {
            JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
        }
        auto arr = info[0].As<Napi::TypedArrayOf<uchar>>();
        auto rows = info[1].As<Napi::Number>();
        auto cols = info[2].As<Napi::Number>();
        auto type = info[3].As<Napi::Number>();
        this->mat = Image::NewMat(arr, rows, cols, type);

#ifdef DEBUG_MATWRAPPER
        cv::namedWindow("Image()", cv::WINDOW_AUTOSIZE);
        cv::imshow("Image()", this->mat);
        cv::waitKey(0);
#endif
    } else  {
        JSErrors::TooManyArguments(env, 4, len);
    }
}
// instance methods
Napi::Value Nodoface::Image::Type(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->type());
}

Napi::Value Nodoface::Image::Rows(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), this->mat->rows);
}

Napi::Value Nodoface::Image::Columns(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->cols);
}

Napi::Value Nodoface::Image::Channels(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), this->mat->channels());
}
// cpp only
cv::Mat Nodoface::Image::GetMat() {
    return *this->mat;
}
