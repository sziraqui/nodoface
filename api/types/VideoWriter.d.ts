import { Image } from "./Image";

export class VideoWriter {
    constructor(file: string, width: number, height: number, fps: number, fourcc: string);
    write(image: Image): undefined;
    release(): undefined;
}