import {Image} from "./Image";
import {Rect} from "./Rect";

export class SequenceCapture {
    constructor();

    open(arguments: string[]): boolean;

    openVideoFile(videoFile: string): boolean;

    openVideoFile(videoFile: string, fx: number, fy: number, cx: number, cy: number): boolean;

    openWebcam(deviceId: number): boolean;

    openWebcam(deviceId: number, width: number, height: number): boolean;

    openWebcam(deviceId: number, width: number, height: number, fx: number, fy: number, cx: number, cy: number): boolean;

    isWebcam(): boolean;

    getNextFrame(): Image;

    getGrayFrame(): Image;

    getFrameNumber(): number;

    isOpened(): boolean;

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