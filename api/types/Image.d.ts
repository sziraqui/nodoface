import { Rect } from './Rect';

export class Image {
    constructor(data: Uint8Array, rows: number, columns: number, type: number);

    width(): number;

    height(): number;

    channels(): number;

    type(): number;

    extract(roi: Rect): Image;

    resize(height: number, width: number): undefined;

    toUint8Array(): Uint8Array;
}