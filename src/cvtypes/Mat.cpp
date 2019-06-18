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
        InstanceMethod("shape", &Nodoface::Image::Shape),
        InstanceMethod("type", &Nodoface::Image::Type)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Image", func);
    return exports;
}

Napi::Object Nodoface::Image::NewObject(Napi::Env env, cv::Mat& mat) {
    std::cout<<"NewObject called\n";
    // Get continuous mat data
    uchar* data;
    size_t length = mat.total() * mat.channels();
    if (mat.isContinuous()) {
        std::cout<<"NewObject mat is continuous\n";
        data = mat.data;
    } else {
        std::cout<<"NewObject mat not continuous\n";
        cv::Mat flatView = mat.reshape(1, length);
        std::vector<uchar> vec = flatView.clone(); // Is clone redundant?
        data = vec.data();
    }
    std::cout<<"NewObject create mat array\n";
    // Create ArrayBuffer from data
    Napi::ArrayBuffer ab = Napi::ArrayBuffer::New(env, data, sizeof(uchar)*length);
    std::cout<<"NewObject create typedArray\n";
    Napi::TypedArrayOf<uchar> arr = Napi::TypedArrayOf<uchar>::New(env, length, ab, 0); // arg0
    std::cout<<"NewObject create mat size\n";
    // Create array for mat dimensions
    std::vector<int> sizeVec(mat.size.dims());
    for(int i = 0; i < mat.size.dims(); ++i) {
        sizeVec[i] = mat.size[i];
        std::cout<<"NewObject: mat.size["<<i<<"]:"<<sizeVec[i]<<std::endl;
    }
    Napi::ArrayBuffer sizeBuf = Napi::ArrayBuffer::New(env, sizeVec.data(), sizeof(int)*sizeVec.size());
    Napi::TypedArrayOf<int> size = Napi::TypedArrayOf<int>::New(env, sizeVec.size(), sizeBuf, 0); // arg1
    std::cout<<"NewObject mat type "<<mat.type()<<std::endl;
    // Create mat type Number
    Napi::Number type = Napi::Number::New(env, mat.type());  // arg2
    std::cout<<"NewObject call constructor.New\n";
    Napi::Object imageObj = Image::constructor.New({ arr, size, type });
    Image* image = Napi::ObjectWrap<Image>::Unwrap(imageObj);
    cv::namedWindow("NewObject", cv::WINDOW_AUTOSIZE);
    cv::imshow("NewObject", image->GetMat());
    cv::waitKey(0);
    return imageObj;
}
// cpp only
cv::Mat Nodoface::Image::NewMat(Napi::TypedArrayOf<uchar> &arr, Napi::TypedArrayOf<int> &size, Napi::Number &type) {
    std::cout<<"newMat called\n";
    // Get mat data
    auto buf = arr.ArrayBuffer();
    std::cout<<"NewMat pixels:"<<arr.ElementLength()<<" dims:"<<size.ElementLength()<<std::endl;
    uchar* data = reinterpret_cast<uchar *>(buf.Data()); // reinterpret_cast for void* to uchar*
    // Get mat size
    auto sizeBuf = size.ArrayBuffer();
    const int* matSize = reinterpret_cast<int *>(sizeBuf.Data());
    for(int i = 0; i < size.ElementLength(); i++)
        std::cout<<"NewMat matSize["<<i<<"]:"<<matSize[i]<<std::endl;
    // Get Mat type
    int matType = type.Int32Value();
    // Create mat
    cv::Mat mat(matSize[0], matSize[1], matType, data);
    std::cout<<"NewMat mat restored\n";
    cv::namedWindow("NewMat", cv::WINDOW_AUTOSIZE);
    cv::imshow("NewMat", mat);
    cv::waitKey(0);
    return mat;
}

// constructor
Nodoface::Image::Image(const Napi::CallbackInfo& info) : ObjectWrap<Nodoface::Image>(info) {
    std::cout<<"inside Mat constructor\n";
    int len = info.Length();
    std::cout<<"info.Length " << len<<std::endl;
    auto env = info.Env();
    if(len == 0 || len == 2) {
        JSErrors::InsufficientArguments(env, 3, 0);
    } else if (len == 1 && info[0].IsObject()) {
        // copy constructor
        std::cout<<"Mat Unwrap start\n";
        Image * img = Napi::ObjectWrap<Image>::Unwrap(info[1].As<Napi::Object>());
        std::cout<<"Mat Unwrap end\n";
        this->mat = img->mat;
    } else if (len == 3) {
        // constructor with data as arrays
        if(!info[0].IsTypedArray()) {
            JSErrors::IncorrectDatatype(env, JSErrors::TYPEDARRAY, 1);
        }
        if(!info[1].IsTypedArray()) {
            JSErrors::IncorrectDatatype(env, JSErrors::TYPEDARRAY, 2);
        }
        if(!info[2].IsNumber()) {
            JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, 3);
        }
        auto arr = info[0].As<Napi::TypedArrayOf<uchar>>();
        auto size = info[1].As<Napi::Int32Array>();
        auto type = info[2].As<Napi::Number>();
        this->mat = Image::NewMat(arr, size, type);
        cv::namedWindow("Image()", cv::WINDOW_AUTOSIZE);
        cv::imshow("Image()", this->mat);
        cv::waitKey(0);
    } else  {
        JSErrors::TooManyArguments(env, 3, len);
    }
    std::cout<<"Mat constructor finish\n";
}
// instance methods
Napi::Value Nodoface::Image::Shape(const Napi::CallbackInfo &info) {
    std::vector<int> vec(this->mat.size.p, this->mat.size.p + this->mat.size.dims());
    vec.push_back(this->mat.channels());
    auto ab = Napi::ArrayBuffer::New(info.Env(), vec.data(), sizeof(int)*vec.size());
    auto arr = Napi::Int32Array::New(info.Env(), vec.size(), ab, 0);
    return arr;
}

Napi::Value Nodoface::Image::Type(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat.type());
}
// cpp only
cv::Mat Nodoface::Image::GetMat() {
    return this->mat;
}