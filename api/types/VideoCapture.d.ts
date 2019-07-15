import { Image } from './Image';

export class VideoCapture {

    constructor();

    open(deviceOrFile: number | string): undefined;

    read(): Image;

    isOpened(): boolean;
}