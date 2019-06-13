//
// Created by sziraqui on 12/6/19.
//

#ifndef NODOFACE_NDARRAY_H
#define NODOFACE_NDARRAY_H
// system includes
#include <vector>
#include <string>
#include <initializer_list>

// opencv includes
#include <opencv2/core/mat.hpp>
#include <opencv2/core/utility.hpp>

// napi
#include <napi.h>


namespace NapiExtras {

    // NdArray handle conversions to/from Napi::ArrayBuffer and cv::Mat
    // By default this stores cv::Mat<uchar> or Array of Numbers
    template <class numericType = uchar>
    class NdArray {
    public:
        // Creating an instance
        static NdArray<numericType> From(Napi::TypedArrayOf<numericType> arr, Napi::Int32Array dims, bool copy = false);
        static NdArray<numericType> From(cv::Mat mat, bool copy = false);

        NdArray(std::vector<int>& shape, numericType* ptr, bool copy = false);
        // Get underlying data
        // instance.Get({0,1,2}) to get element at (0,1,2) index of input cv::Mat or Array
//        numericType Get(std::initializer_list<int> index);
//        // instance.Set(8, {0,1,2}) to set value of element at (0,1,2) index of cv::Mat or Array
//        bool Set(numericType value, std::initializer_list<int> index);

        // matType must be as returned by original mat.type()
        cv::Mat ToMat(int matType);
    private:
        // pointer to actual array backing cv::Mat or ArrayBuffer
        numericType* ptr;
        // Values of buffer will be copied to this vector if needed
        std::vector<numericType> data;
        // actual dimensions of cv::Mat or multi-dimension array passed as array buffer
        std::vector<int> shape;

        // Private constructor
        NdArray(){}
    };

    template <class  numericType>
    NdArray<numericType> NdArray<numericType>::From(Napi::TypedArrayOf<numericType> arr, Napi::Int32Array dims, bool copy) {
        // Copy shape information
        std::vector<int> shape(dims.ElementLength());
        for(uint32_t i = 0u; i < shape.size(); ++i){
            shape[i] = dims[i];
        }
        // Get data buffer of typed array
        Napi::ArrayBuffer buf = arr.ArrayBuffer();
        numericType* raw = reinterpret_cast<numericType*>(buf.Data());
        if(copy) {
            // Copy buffer data into a vector
            uint32_t bufLen = buf.ByteLength()/sizeof(numericType);
            std::vector<numericType> dataCopy(raw, bufLen);
        }
        return NdArray<numericType>(raw, shape);
    }

    template <class numericType>
    NdArray<numericType> NdArray<numericType>::From(cv::Mat mat, bool copy) {
        // Copy shape information
        std::vector<int> shape;
        for(int i = 0; i < mat.size.dims(); ++i) {
            shape.push_back(mat.size[i]);
            std::cout<<"FromMat:shape["<<i<<"]="<<shape[i]<<std::endl;
        }
        // Get reference to underlying array ptr
        numericType* raw = mat.data;
        cv::Mat matCopy;
        std::vector<numericType> data;
        std::cout<<"FromMat:mat.isContinuous()"<<mat.isContinuous()<<std::endl;
        if(!mat.isContinuous()){
            matCopy = mat.clone();
            raw = matCopy.data;
            std::cout<<"FromMat:cloned"<<data.size()<<std::endl;
        }
        return NdArray<numericType>(shape, raw, copy);
    }

    template <class numericType>
    NdArray<numericType>::NdArray(std::vector<int>& shape, numericType* ptr, bool copy) {
        this->ptr = ptr;
        this->shape = shape;
        if(copy) {
            uint total = 0;
            for(auto d: shape) total*=d;
            std::vector<numericType> dataCopy(ptr, ptr + total);
            this->data = dataCopy;
        }
    }

    template <class numericType>
    cv::Mat NdArray<numericType>::ToMat(int matType) {
        const int * sizes = const_cast<int *>(this->shape.data()); // reference to internal array
        cv::Mat mat(this->shape.size(), sizes, matType, this->ptr);
        return mat;
    }

}

#endif //NODOFACE_NDARRAY_H
