export class Image {
    constructor(data: Uint8Array, rows: number, columns: number, type: number);

    width(): number;

    height(): number;

    channels(): number;

    type(): number;
}