//
// Created by sziraqui on 7/6/19.
//

#ifndef NODOFACE_SEQUENCECAPTURE_H
#define NODOFACE_SEQUENCECAPTURE_H
// system includes
#include <vector>
#include <string>

// opencv includes
#include <opencv/cv.h>

// OpenFace includes
#include <OpenFace/SequenceCapture.h>

// napi
#include <napi.h>

// locals
#include "../extras/ndarray.h"
#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"
#include "../cvtypes/Mat.h"

namespace Nodoface {

class SequenceCapture : public Napi::ObjectWrap<Nodoface::SequenceCapture>{

    public:
        SequenceCapture(const Napi::CallbackInfo& info);
        static Napi::Object Init(Napi::Env env, Napi::Object exports);

    private:
        static Napi::FunctionReference constructor;

        // Opening based on command line arguments
        // bool Open(std::vector<std::string>& arguments);
        Napi::Value Open(const Napi::CallbackInfo& info);

        // Direct opening

        // Webcam
        // bool OpenWebcam(int device_id, int image_width = 640, int image_height = 480, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
        Napi::Value OpenWebcam(const Napi::CallbackInfo& info);

        // Image sequence in the directory
        // bool OpenImageSequence(std::string directory, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
        Napi::Value OpenImageSequence(const Napi::CallbackInfo& info);

        // Video file
        // bool OpenVideoFile(std::string video_file, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
        Napi::Value OpenVideoFile(const Napi::CallbackInfo& info);

        // bool IsWebcam() { return is_webcam; }
        Napi::Value IsWebcam(const Napi::CallbackInfo& info);

        // Getting the next frame
        // cv::Mat GetNextFrame();
        Napi::Value GetNextFrame(const Napi::CallbackInfo& info);

        // Getting the most recent grayscale frame (need to call GetNextFrame first)
        // cv::Mat_<uchar> GetGrayFrame();
        Napi::Value GetGrayFrame(const Napi::CallbackInfo& info);

        // Parameters describing the sequence and it's progress
        // double GetProgress();
        Napi::Value GetProgress(const Napi::CallbackInfo& info);

        // size_t GetFrameNumber() { return frame_num; }
        Napi::Value GetFrameNumber(const Napi::CallbackInfo& info);

        // bool IsOpened();
        Napi::Value IsOpened(const Napi::CallbackInfo& info);

        // void Close();
        Napi::Value Close(const Napi::CallbackInfo& info);

        // GetSet for public variables
        // int image_width;
        Napi::Value GetFrameWidth(const Napi::CallbackInfo& info);
        Napi::Value SetFrameWidth(const Napi::CallbackInfo& info);

        // int image_height
        Napi::Value GetFrameHeight(const Napi::CallbackInfo& info);
        Napi::Value SetFrameHeight(const Napi::CallbackInfo& info);

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
        Utilities::SequenceCapture *sequenceCapture;

        // double fps;
        Napi::Value GetFPS(const Napi::CallbackInfo& info);
        Napi::Value SetFPS(const Napi::CallbackInfo& info);

        // double time_stamp;
        Napi::Value GetTimeStamp(const Napi::CallbackInfo& info);
        Napi::Value SetTimeStamp(const Napi::CallbackInfo& info);

        // Name of the video file, image directory, or the webcam
        // std::string name;
        Napi::Value GetName(const Napi::CallbackInfo& info);
        Napi::Value SetName(const Napi::CallbackInfo& info);

        // Allows to differentiate if failed because no input specified or if failed to open a specified input
        // bool no_input_specified;
        Napi::Value GetNoInputSpecified(const Napi::CallbackInfo& info);
        Napi::Value SetNoInputSpecified(const Napi::CallbackInfo& info);

        // Storing the captured data queue
        // static const int CAPTURE_CAPACITY = 200; // 200 MB
        static Napi::Value GetCaptureCapacity(const Napi::CallbackInfo& info);

    };
}

#endif //NODOFACE_SEQUENCECAPTURE_H
