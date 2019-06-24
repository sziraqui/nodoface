//
// Created by sziraqui on 3/6/19.
//

#ifndef NODOFACE_IMAGECAPTURE_H
#define NODOFACE_IMAGECAPTURE_H

// System includes
#include <vector>
#include <string>

// OpenCV includes
#include<opencv2/opencv.hpp>

// OpenFace includes
#include <OpenFace/ImageCapture.h>

// local includes
#include "../extras/ndarray.h"
#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"
#include "../cvtypes/Mat.h"

#include <napi.h>

namespace Nodoface {
class ImageCapture : public Napi::ObjectWrap<ImageCapture> {
public:
    ImageCapture(const Napi::CallbackInfo& info);
    static Napi::Object Init(Napi::Env env, Napi::Object exports);

private:
    static Napi::FunctionReference constructor;
    // Opening based on command line arguments
    // bool Open(std::vector<std::string>& arguments);
    Napi::Value Open(const Napi::CallbackInfo& info);
    // Direct opening

    // Image sequence in the directory
    // bool OpenDirectory(std::string directory, std::string bbox_directory="", float fx = -1, float fy = -1, float cx = -1, float cy = -1);
    Napi::Value OpenDirectory(const Napi::CallbackInfo& info);

    // Video file
    // bool OpenImageFiles(const std::vector<std::string>& image_files, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
    Napi::Value OpenImageFiles(const Napi::CallbackInfo& info);

    // Getting the next frame
    // cv::Mat GetNextImage();
    Napi::Value GetNextImage(const Napi::CallbackInfo& info);

    // Getting the most recent grayscale frame (need to call GetNextImage first)
    // cv::Mat_<uchar> GetGrayFrame();
    Napi::Value GetGrayFrame(const Napi::CallbackInfo& info);

    // Return bounding boxes associated with the image (if defined)
    // std::vector<cv::Rect_<float> > GetBoundingBoxes();
    Napi::Value GetBoundingBoxes(const Napi::CallbackInfo& info);

    // Parameters describing the sequence and it's progress (what's the proportion of images opened)
    // double GetProgress();
    Napi::Value GetProgress(const Napi::CallbackInfo& info);

    // GetSet for public variables
    // int image_width;
    Napi::Value GetImageWidth(const Napi::CallbackInfo& info);
    Napi::Value SetImageWidth(const Napi::CallbackInfo& info);

    // int image_height
    Napi::Value GetImageHeight(const Napi::CallbackInfo& info);
    Napi::Value SetImageHeight(const Napi::CallbackInfo& info);

    // float fx, fy, cx, cy;
    Napi::Value GetFx(const Napi::CallbackInfo& info);
    Napi::Value SetFx(const Napi::CallbackInfo& info);
    Napi::Value GetFy(const Napi::CallbackInfo& info);
    Napi::Value SetFy(const Napi::CallbackInfo& info);
    Napi::Value GetCx(const Napi::CallbackInfo& info);
    Napi::Value SetCx(const Napi::CallbackInfo& info);
    Napi::Value GetCy(const Napi::CallbackInfo& info);
    Napi::Value SetCy(const Napi::CallbackInfo& info);
    // Reference to actual class
    Utilities::ImageCapture *imageCapture;

};
}

#endif //NODOFACE_IMAGECAPTURE_H
