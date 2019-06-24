import {Image} from "./Image";

export class FaceDetectionMTCNN {
    constructor();
    constructor(modelFile: string);
    constructor(instance: FaceDetectionMTCNN);
    detectFaces(image: Image);
    detectFaces(image: Image, minFace: number);
    detectFaces(image: Image, minFace: number, t1: number);
    detectFaces(image: Image, minFace: number, t1: number, t2: number);
    detectFaces(image: Image, minFace: number, t1: number, t2: number, t3: number);
    read(modelFile: string);
    empty(): boolean;
}