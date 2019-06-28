import * as path from 'path';
import { expect } from 'chai';
import { Image, readImage } from '../';

describe('Image', () => {
    let type = 16; // CV_U8C3
    let rows = 4;
    let cols = 8;
    let arr = new Uint8Array(rows*cols*3);
    let image;
    it('Image from JS', () => {
        image = new Image(arr, rows, cols, type);
        expect(image).to.instanceof(Image);
    });
    it('Image from C++', () => {
        let file = path.join(__dirname, 'samples', 'frames', 'single_face_01.jpg');
        cols = 640;
        rows = 480;
        image = readImage(file);
        expect(image).to.instanceof(Image);
    });
    it('Image.height()', () => {
        expect(image.height()).to.equal(rows);
    });
    it('Image.width()', () => {
        expect(image.width()).to.equal(cols);
    });
    it('Image.type()', () => {
        expect(image.type()).to.equal(type);
    });
});