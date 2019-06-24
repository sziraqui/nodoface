import {Image} from "./Image";
import {DetectionResult} from "./DetectionResult";

export class FaceDetectionMTCNN {
    constructor();
    constructor(modelFile: string);
    constructor(instance: FaceDetectionMTCNN);

    detectFaces(image: Image): DetectionResult;
    detectFaces(image: Image, minFace: number): DetectionResult;
    detectFaces(image: Image, minFace: number, t1: number): DetectionResult;
    detectFaces(image: Image, minFace: number, t1: number, t2: number): DetectionResult;
    detectFaces(image: Image, minFace: number, t1: number, t2: number, t3: number): DetectionResult;

    read(modelFile: string): undefined;

    empty(): boolean;
}