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
    getFrameWidth(): number;
    getFrameHeight(): number;
    setFrameWidth(): number;
    setFrameHeight(): number;
    getFx(): number;
    getFy(): number;
    getCx(): number;
    getCy(): number;
    setFx(fx: number);
    setFy(fy: number);
    setCx(cx: number);
    setCy(cy: number);
    getName(name: string);
    setName(name: string);
    getNoInputSpecified(): boolean;
    setNoInputSpecified(): boolean;
    getCaptureCapacity(): number;
    getFPS(): number;
    setFPS(fps: number);
}