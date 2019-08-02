import * as path from 'path';
import { expect } from 'chai';
import { Image, readImage, saveImage, showImage, waitKey } from '../';

describe('Image', () => {
    let type = 16; // CV_U8C3
    let rows = 4;
    let cols = 8;
    let arr = new Uint8Array(rows * cols * 3);
    let image: Image;
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
        saveImage(path.join(__dirname, 'outputs', 'Test_read_' + path.basename(file)), image);
    });
    it('Image extract ROI', () => {
        let file = path.join(__dirname, 'samples', 'frames', 'single_face_01.jpg');
        cols = 640;
        rows = 480;
        image = readImage(file);
        let roi = { x: 0, y: 0, width: cols, height: rows };
        let region = image.extract(roi);
        expect(region.height()).to.equal(roi.height);
        expect(region.width()).to.equal(roi.width);
    });
    it('Image extract ROI - out of range rect', () => {
        let file = path.join(__dirname, 'samples', 'frames', 'single_face_01.jpg');
        cols = 640;
        rows = 480;
        image = readImage(file);
        let roi = { x: -30, y: rows / 2, width: cols, height: rows };
        let region = image.extract(roi);
        expect(region.height()).to.equal(image.height() - roi.y);
        expect(region.width()).to.equal(roi.width);
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

    it('Image.toUint8Array', () => {
        rows = 2;
        cols = 4;
        arr = new Uint8Array(rows * cols * 3);
        let offset = 0;
        for (let i = 0; i < rows; i++) {
            for (let j = 0; j < cols; j++) {
                for (let k = 0; k < 3; k++) {
                    arr[offset] = i + j + k;
                    offset++;
                }
            }
        }
        image = new Image(arr, rows, cols, type);
        let flatImg = image.toUint8Array();
        expect(flatImg.length).to.equal(arr.length);
        offset = 0;
        flatImg.forEach((val, i) => {
            expect(val).to.equal(arr[i]);
        });
    });
    it.only('Image.resize()', () => {
        let file = path.join(__dirname, 'samples', 'frames', 'single_face_01.jpg');
        cols = 640;
        rows = 480;
        image = readImage(file);
        image.resize(320, 240);
        saveImage(path.join(__dirname, 'outputs', 'single_face_01_resize.jpg'), image);
        expect(image.height()).to.equal(240);
        expect(image.width()).to.equal(320);
    });
});