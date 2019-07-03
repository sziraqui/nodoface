//
// Created by sziraqui on 3/7/19.
//

#ifndef NODOFACE_MATIMAGE_H
#define NODOFACE_MATIMAGE_H
#include <vector>

#include <opencv2/core/mat.hpp>

#include <napi.h>

#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"

namespace Nodoface {
    // Wraps OpenCV Mat partially for sending and receiving Mat objects to/from node
    template <class numerictType>
    class MatImage : public Napi::ObjectWrap<MatImage<numerictType>> {

    public:

        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        static Napi::Value NewObject(Napi::Env env, cv::Mat& mat);

        static cv::Mat* NewMat(Napi::TypedArrayOf<numerictType>& arr, Napi::Number& rows, Napi::Number& cols, Napi::Number& type);

        MatImage(const Napi::CallbackInfo& info);

        cv::Mat GetMat();

        ~MatImage();

        cv::Mat* mat;

        static Napi::FunctionReference constructor;

        Napi::Value Type(const Napi::CallbackInfo& info);

        Napi::Value Rows(const Napi::CallbackInfo& info);

        Napi::Value Columns(const Napi::CallbackInfo& info);

        Napi::Value Channels(const Napi::CallbackInfo& info);
    };
}

template <class numericType>
Napi::FunctionReference Nodoface::MatImage<numericType>::constructor;

template <class numericType>
Napi::Value Nodoface::MatImage<numericType>::NewObject(Napi::Env env, cv::Mat& mat) {
    Napi::EscapableHandleScope scope(env);
    // Get continuous mat data

    size_t length = mat.total() * mat.channels();
    if(mat.isContinuous()) {
        mat =  cv::Mat(mat); // ensures mat is continuous and also prevents segfault
    }

    // Create ArrayBuffer from data
    Napi::ArrayBuffer ab = Napi::ArrayBuffer::New(env, mat.data, sizeof(numericType)*length);
    Napi::TypedArrayOf<numericType> arr = Napi::TypedArrayOf<numericType>::New(env, length, ab, 0); // arg1
    // Mat dimensions
    Napi::Number rows = Napi::Number::New(env, mat.rows); // arg2
    Napi::Number cols = Napi::Number::New(env, mat.cols); // arg3
    // Create mat type Number
    Napi::Number type = Napi::Number::New(env, mat.type());  // arg4
    // Call constructor
    Napi::Object imageObj = MatImage<numericType>::constructor.New({ arr, rows, cols, type });

    return scope.Escape(imageObj);
}
// cpp only
template <class numericType>
cv::Mat* Nodoface::MatImage<numericType>::NewMat(Napi::TypedArrayOf<numericType> &arr, Napi::Number& rows, Napi::Number& cols, Napi::Number& type) {
    // Get mat data
    auto buf = arr.ArrayBuffer();
    numericType* data = reinterpret_cast<numericType *>(buf.Data()); // reinterpret_cast for void* to uchar*
    // Get mat size
    size_t matRows = rows.Int32Value();
    size_t matCols = cols.Int32Value();
    // Get Mat type
    int matType = type.Int32Value();
    // Create mat
    cv::Mat* mat = new cv::Mat(matRows, matCols, matType, data);

    return mat;
}

// constructor
template <class numericType>
Nodoface::MatImage<numericType>::MatImage(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Nodoface::MatImage<numericType>>(info) {
    int len = info.Length();
    auto env = info.Env();
    if(len == 0 || len == 2) {
        JSErrors::InsufficientArguments(env, 4, 0);
    } else if (len == 1 && info[0].IsObject()) {
        // copy constructor
        MatImage<numericType> * img = Napi::ObjectWrap<Nodoface::MatImage<numericType>>::Unwrap(info[1].As<Napi::Object>());
        this->mat = img->mat;
    } else if (len == 4) {
        // constructor with data as arrays
        if(!info[0].IsTypedArray()) {
            JSErrors::IncorrectDatatype(env, JSErrors::TYPEDARRAY, 1);
        }
        for (int i = 1; i <= 3 && !info[i].IsNumber(); i++) {
            JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
        }
        auto arr = info[0].As<Napi::TypedArrayOf<numericType>>();
        auto rows = info[1].As<Napi::Number>();
        auto cols = info[2].As<Napi::Number>();
        auto type = info[3].As<Napi::Number>();
        this->mat = MatImage<numericType>::NewMat(arr, rows, cols, type);

    } else  {
        JSErrors::TooManyArguments(env, 4, len);
    }
}
// instance methods
template <class numericType>
Napi::Value Nodoface::MatImage<numericType>::Type(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->type());
}

template <class numericType>
Napi::Value Nodoface::MatImage<numericType>::Rows(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), this->mat->rows);
}

template <class numericType>
Napi::Value Nodoface::MatImage<numericType>::Columns(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->cols);
}

template <class numericType>
Napi::Value Nodoface::MatImage<numericType>::Channels(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), this->mat->channels());
}
// cpp only
template <class numericType>
cv::Mat Nodoface::MatImage<numericType>::GetMat() {
    return *this->mat;
}

template <class numericType>
Nodoface::MatImage<numericType>::~MatImage<numericType>() {
    delete[] this->mat->data;
    delete this->mat;
}
#endif //NODOFACE_MATIMAGE_H
