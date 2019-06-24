//
// Created by sziraqui on 22/6/19.
//

#include "MatInt.h"

Napi::FunctionReference Nodoface::IntImage::constructor;

// static methods
Napi::Object Nodoface::IntImage::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "IntImage", {
            InstanceMethod("type", &Nodoface::IntImage::Type),
            InstanceMethod("height", &Nodoface::IntImage::Rows),
            InstanceMethod("width", &Nodoface::IntImage::Columns),
            InstanceMethod("channels", &Nodoface::IntImage::Channels)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("IntImage", func);
    return exports;
}

Napi::Value Nodoface::IntImage::NewObject(Napi::Env env, cv::Mat_<int>& mat) {
    Napi::EscapableHandleScope scope(env);
    // Get continuous mat data

    size_t length = mat.total() * mat.channels();
    if(mat.isContinuous()) {
        mat =  cv::Mat_<int>(mat); // ensures mat is continuous and also prevents segfault
    }

    // Create ArrayBuffer from data
    Napi::ArrayBuffer ab = Napi::ArrayBuffer::New(env, mat.data, sizeof(int)*length);
    Napi::TypedArrayOf<int> arr = Napi::TypedArrayOf<int>::New(env, length, ab, 0); // arg1
    // Mat_<int> dimensions
    Napi::Number rows = Napi::Number::New(env, mat.rows); // arg2
    Napi::Number cols = Napi::Number::New(env, mat.cols); // arg3
    // Create mat type Number
    Napi::Number type = Napi::Number::New(env, mat.type());  // arg4
    // Call constructor
    Napi::Object imageObj = IntImage::constructor.New({ arr, rows, cols, type });

    return scope.Escape(imageObj);
}
// cpp only
cv::Mat_<int>* Nodoface::IntImage::NewMat(Napi::TypedArrayOf<int> &arr, Napi::Number& rows, Napi::Number& cols, Napi::Number& type) {
    // Get mat data
    auto buf = arr.ArrayBuffer();
    int* data = reinterpret_cast<int *>(buf.Data()); // reinterpret_cast for void* to int*
    // Get mat size
    size_t matRows = rows.Int32Value();
    size_t matCols = cols.Int32Value();
    // Get Mat_<int> type
    int matType = type.Int32Value();
    // Create mat
    cv::Mat_<int>* mat = new cv::Mat_<int>(matRows, matCols, data);

    return mat;
}

// constructor
Nodoface::IntImage::IntImage(const Napi::CallbackInfo& info) : ObjectWrap<Nodoface::IntImage>(info) {
    int len = info.Length();
    auto env = info.Env();
    if(len == 0 || len == 2) {
        JSErrors::InsufficientArguments(env, 4, 0);
    } else if (len == 1 && info[0].IsObject()) {
        // copy constructor
        IntImage * img = Napi::ObjectWrap<Nodoface::IntImage>::Unwrap(info[1].As<Napi::Object>());
        this->mat = img->mat;
    } else if (len == 4) {
        // constructor with data as arrays
        if(!info[0].IsTypedArray()) {
            JSErrors::IncorrectDatatype(env, JSErrors::TYPEDARRAY, 1);
        }
        for (int i = 1; i <= 3 && !info[i].IsNumber(); i++) {
            JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
        }
        auto arr = info[0].As<Napi::TypedArrayOf<int>>();
        auto rows = info[1].As<Napi::Number>();
        auto cols = info[2].As<Napi::Number>();
        auto type = info[3].As<Napi::Number>();
        this->mat = IntImage::NewMat(arr, rows, cols, type);

    } else  {
        JSErrors::TooManyArguments(env, 4, len);
    }
}
// instance methods
Napi::Value Nodoface::IntImage::Type(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->type());
}

Napi::Value Nodoface::IntImage::Rows(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), this->mat->rows);
}

Napi::Value Nodoface::IntImage::Columns(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->cols);
}

Napi::Value Nodoface::IntImage::Channels(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), this->mat->channels());
}
// cpp only
cv::Mat_<int> Nodoface::IntImage::GetMat() {
    return *this->mat;
}

Nodoface::IntImage::~IntImage() {
    delete[] this->mat->data;
    delete this->mat;
}