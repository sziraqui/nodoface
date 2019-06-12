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
#include <opencv2/opencv.hpp>

// local includes
#include "../jserrors/JSErrors.h"

namespace NapiExtras {

    // Recursively find length of each sub-array and collect it in a vector
    static void CalculateShape(Napi::Value value, vector<uint32_t>& shape);

    // Recurse an array to collect its elements in a flat vector
    // dest is assumed to be pre-allocated to fit the array
    template<class numericType = uint8_t>
    static void FlattenArray(Napi::Value value, std::vector<numericType>& dest, uint32_t index = 0u) {
        if(!value.IsArray()) {
            return;
        }
        Napi::Array arr = value.As<Napi::Array>();
        // test each value inside array
        // If its a number, append it, if its an Array, recurse, else throw error
        for(uint32_t i = 0u; i < arr.Length(); ++i) {
            Napi::Value nextVal = arr.Get(i);
            if(nextVal.IsNumber()) {
                numericType num = nextVal.As<Napi::Number>().DoubleValue();
                dest.push_back(num);
            } else if(nextVal.IsArray()) {
                return FlattenArray(value, dest, index + 1);
            } else {
                stderr
                        << "E/FlattenArray: Invalid argument. Expected Napi::Array or Napi::Number type. Got "
                        << typeid(value).name() << std::endl;
                return;
            }
        }
    }

    // NdArray handle all numeric datatypes like cv::Mat, vector of ints,floats, etc, and Napi::Array
    // By default this stores cv::Mat<uchar> or Array of Numbers
    template <class numericType = uint8_t >
    class NdArray {
    public:
        // Creating an instance
        static NdArray From(Napi::Array nparr);
        static NdArray From(cv::Mat<numericType> mat);

        // Get underlying data
        // instance.Get({0,1,2}) to get element at (0,1,2) index of input cv::Mat or Array
        numericType Get(std::initializer_list index)
        // instance.Set(8, {0,1,2}) to set value of element at (0,1,2) index of cv::Mat or Array
        bool Set(numericType value, std::initializer_list index);
    private:
        std::vector<numericType> data;
        std::vector<uint32_t > shape;
    };

    static void CalculateShape(Napi::Value value, vector <uint32_t>& shape) {
        if(!value.IsArray()) {
            return;
        }
        Napi::Array arr = value.As<Napi::Array>();

        shape.push_back(arr.Length());
        Napi::Value nextVal = arr.Get(0u);
        return CalculateShape(nextVal, shape);
    }

    static NdArray::From(Napi::Array nparr) {
        // Find dimensions of array
        std::vector<uint32_t> shape;
        CalculateShape(nparr.As<Napi::Value>(), shape);

    }


}

#endif //NODOFACE_NDARRAY_H
