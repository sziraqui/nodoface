//
// Created by sziraqui on 22/6/19.
//

#include "MatFloat.h"


Napi::FunctionReference Nodoface::FloatImage::constructor;

// static methods
Napi::Object Nodoface::FloatImage::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FloatImage", {
            InstanceMethod("type", &Nodoface::FloatImage::Type),
            InstanceMethod("height", &Nodoface::FloatImage::Rows),
            InstanceMethod("width", &Nodoface::FloatImage::Columns),
            InstanceMethod("channels", &Nodoface::FloatImage::Channels)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("FloatImage", func);
    return exports;
}

Napi::Value Nodoface::FloatImage::NewObject(Napi::Env env, cv::Mat_<float>& mat) {
    Napi::EscapableHandleScope scope(env);
    // Get continuous mat data

    size_t length = mat.total() * mat.channels();
    if(mat.isContinuous()) {
        mat =  cv::Mat_<float>(mat); // ensures mat is continuous and also prevents segfault
    }

    // Create ArrayBuffer from data
    Napi::ArrayBuffer ab = Napi::ArrayBuffer::New(env, mat.data, sizeof(float)*length);
    Napi::TypedArrayOf<float> arr = Napi::TypedArrayOf<float>::New(env, length, ab, 0); // arg1
    // Mat_<float> dimensions
    Napi::Number rows = Napi::Number::New(env, mat.rows); // arg2
    Napi::Number cols = Napi::Number::New(env, mat.cols); // arg3
    // Create mat type Number
    Napi::Number type = Napi::Number::New(env, mat.type());  // arg4
    // Call constructor
    Napi::Object imageObj = FloatImage::constructor.New({ arr, rows, cols, type });
#ifdef DEBUG_MATWRAPPER
    FloatImage* image = Napi::ObjectWrap<FloatImage>::Unwrap(imageObj);
    cv::namedWindow("NewObject", cv::WINDOW_AUTOSIZE);
    cv::imshow("NewObject", image->GetMat());
    cv::waitKey(0);
#endif
    return scope.Escape(imageObj);
}
// cpp only
cv::Mat_<float>* Nodoface::FloatImage::NewMat(Napi::TypedArrayOf<float> &arr, Napi::Number& rows, Napi::Number& cols, Napi::Number& type) {
    // Get mat data
    auto buf = arr.ArrayBuffer();
    float* data = reinterpret_cast<float *>(buf.Data()); // reinterpret_cast for void* to float*
    // Get mat size
    size_t matRows = rows.Int32Value();
    size_t matCols = cols.Int32Value();
    // Get Mat_<float> type
    int matType = type.Int32Value();
    // Create mat
    cv::Mat_<float>* mat = new cv::Mat_<float>(matRows, matCols, data);
#ifdef DEBUG_MATWRAPPER
    cv::namedWindow("NewMat", cv::WINDOW_AUTOSIZE);
    cv::imshow("NewMat", mat);
    cv::waitKey(0);
#endif
    return mat;
}

// constructor
Nodoface::FloatImage::FloatImage(const Napi::CallbackInfo& info) : ObjectWrap<Nodoface::FloatImage>(info) {
    int len = info.Length();
    auto env = info.Env();
    if(len == 0 || len == 2) {
        JSErrors::InsufficientArguments(env, 4, 0);
    } else if (len == 1 && info[0].IsObject()) {
        // copy constructor
        FloatImage * img = Napi::ObjectWrap<Nodoface::FloatImage>::Unwrap(info[1].As<Napi::Object>());
        this->mat = img->mat;
    } else if (len == 4) {
        // constructor with data as arrays
        if(!info[0].IsTypedArray()) {
            JSErrors::IncorrectDatatype(env, JSErrors::TYPEDARRAY, 1);
        }
        for (int i = 1; i <= 3 && !info[i].IsNumber(); i++) {
            JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
        }
        auto arr = info[0].As<Napi::TypedArrayOf<float>>();
        auto rows = info[1].As<Napi::Number>();
        auto cols = info[2].As<Napi::Number>();
        auto type = info[3].As<Napi::Number>();
        this->mat = FloatImage::NewMat(arr, rows, cols, type);

#ifdef DEBUG_MATWRAPPER
        cv::namedWindow("FloatImage()", cv::WINDOW_AUTOSIZE);
        cv::imshow("FloatImage()", this->mat);
        cv::waitKey(0);
#endif
    } else  {
        JSErrors::TooManyArguments(env, 4, len);
    }
}
// instance methods
Napi::Value Nodoface::FloatImage::Type(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->type());
}

Napi::Value Nodoface::FloatImage::Rows(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), this->mat->rows);
}

Napi::Value Nodoface::FloatImage::Columns(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->cols);
}

Napi::Value Nodoface::FloatImage::Channels(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), this->mat->channels());
}
// cpp only
cv::Mat_<float> Nodoface::FloatImage::GetMat() {
    return *this->mat;
}

Nodoface::FloatImage::~FloatImage() {
    delete[] this->mat->data;
    delete this->mat;
}