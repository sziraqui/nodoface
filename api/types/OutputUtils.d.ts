import {Image} from "./Image";

export function readImage(filePath: string): Image;
export function readImage(filePath: string, asGray: boolean): Image;

export function showImage(image: Image);
export function showImage(image: Image, windowName: string);
export function showImage(image: Image, windowName: string, asGray: boolean);

export function destroyWindow(windowName: string);

export function destroyAllWindows();

export function waitKey(milliseconds: number): number;