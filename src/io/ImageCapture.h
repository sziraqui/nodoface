//
// Created by sziraqui on 3/6/19.
//

#ifndef NODOFACE_IMAGECAPTURE_H
#define NODOFACE_IMAGECAPTURE_H


#include <OpenFace/ImageCapture.h>
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
    Napi::Boolean Open(const Napi::CallbackInfo& info);
    // Direct opening

    // Image sequence in the directory
    // bool OpenDirectory(std::string directory, std::string bbox_directory="", float fx = -1, float fy = -1, float cx = -1, float cy = -1);
    Napi::Boolean OpenDirectory(const Napi::CallbackInfo& info);

    // Video file
    // bool OpenImageFiles(const std::vector<std::string>& image_files, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
    Napi::Boolean OpenImageFiles(const Napi::CallbackInfo& info);

    // Getting the next frame
    // cv::Mat GetNextImage();
    Napi::Uint8Array GetNextImage(const Napi::CallbackInfo& info);

    // Getting the most recent grayscale frame (need to call GetNextImage first)
    // cv::Mat_<uchar> GetGrayFrame();
    Napi::Uint8Array GetGrayFrame(const Napi::CallbackInfo& info);

    // Return bounding boxes associated with the image (if defined)
    // std::vector<cv::Rect_<float> > GetBoundingBoxes();
    Napi::TypedArray GetBoundingBoxes(const Napi::CallbackInfo& info);

    // Parameters describing the sequence and it's progress (what's the proportion of images opened)
    // double GetProgress();
    Napi::Number GetProgress(const Napi::CallbackInfo& info);

    // GetSet for public variables
    // int image_width;
    Napi::Number GetImageWidth(const Napi::CallbackInfo& info);
    Napi::Boolean SetImageWidth(const Napi::CallbackInfo& info);

    // int image_height
    Napi::Number GetImageHeight(const Napi::CallbackInfo& info);
    Napi::Boolean SetImageHeight(const Napi::CallbackInfo& info);

    // float fx, fy, cx, cy;
    Napi::Number GetFx(const Napi::CallbackInfo& info);
    Napi::Boolean SetFx(const Napi::CallbackInfo& info);
    Napi::Number GetFy(const Napi::CallbackInfo& info);
    Napi::Boolean SetFy(const Napi::CallbackInfo& info);
    Napi::Number GetCx(const Napi::CallbackInfo& info);
    Napi::Boolean SetCx(const Napi::CallbackInfo& info);
    Napi::Number GetCy(const Napi::CallbackInfo& info);
    Napi::Boolean SetCy(const Napi::CallbackInfo& info);
    // Reference to actual class
    Utilities::ImageCapture *imageCapture;

};
}


#endif //NODOFACE_IMAGECAPTURE_H
