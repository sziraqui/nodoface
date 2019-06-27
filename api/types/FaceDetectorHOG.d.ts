import {Image} from "./Image";

export class FaceDetectorHOG {
    constructor();
    constructor(modelFile: string);
    constructor(instance: FaceDetectorHOG);

    detectFaces(image: Image);
    detectFaces(image: Image, minWidth: number);
    detectFaces(image: Image, minWidth: number, roi: number);

    load(modelFile: string): undefined;

    empty(): boolean;
}