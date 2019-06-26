import {Image} from "./Image";
import {Rect} from "./Rect";

export interface SequenceCapture {
    constructor();

    open(arguments: string[]): boolean;

    openVideoFile(videoFile: string): boolean;

    openVideoFile(videoFile: string, fx: number, fy: number, cx: number, cy: number): boolean;

    openWebCam(deviceId: number): boolean;

    openWebCam(deviceId: number, width: number, height: number): boolean;

    openWebCam(deviceId: number, width: number, height: number, fx: number, fy: number, cx: number, cy: number): boolean;

    isWebcam(): boolean;

    getNextFrame(): Image;

    getGrayFrame(): Image;

    getFrameNumber(): number;

    isOpened(): boolean;

    close();

    getBoundingBoxes(): Rect[];

    getProgress(): number;

    width: number;

    height: number;

    fx: number;

    fy: number;

    cx: number;

    cy: number;

    name: string;

    noInputSpecified: boolean;

    getCaptureCapacity(): number;

    fps: number;
}