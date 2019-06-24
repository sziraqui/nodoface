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

    close(): undefined;

    getBoundingBoxes(): Rect[];

    getProgress(): number;

    getFrameWidth(): number;

    getFrameHeight(): number;

    setFrameWidth(width: number): undefined;

    setFrameHeight(height: number): undefined;

    getFx(): number;

    getFy(): number;

    getCx(): number;

    getCy(): number;

    setFx(fx: number): undefined;

    setFy(fy: number): undefined;

    setCx(cx: number): undefined;

    setCy(cy: number): undefined;

    getName(): number;

    setName(name: string): undefined;

    getNoInputSpecified(): boolean;

    setNoInputSpecified(flag: boolean): undefined;

    getCaptureCapacity(): number;

    getFPS(): number;

    setFPS(fps: number): undefined;
}