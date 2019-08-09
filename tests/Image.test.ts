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
    it('Image.resize()', () => {
        let file = path.join(__dirname, 'samples', 'frames', 'single_face_01.jpg');
        cols = 640;
        rows = 480;
        image = readImage(file);
        image.resize(320, 240);
        saveImage(path.join(__dirname, 'outputs', 'single_face_01_resize.jpg'), image);
        expect(image.height()).to.equal(240);
        expect(image.width()).to.equal(320);
    });
    it('Image.fromBase64()', () => {
        const base64Img = "iVBORw0KGgoAAAANSUhEUgAAABoAAAAgCAYAAAAMq2gFAAAABHNCSVQICAgIfAhkiAAAABl0RVh0U29mdHdhcmUAZ25vbWUtc2NyZWVuc2hvdO8Dvz4AAAL6SURBVEiJ3dY9aFNRFMDx/817N3mxTZu8GGOTipWujRYdFMHPooNdimDrUKcuBbM51CAoopOKooIuZlQKKoiLX/iFSylVSotLSpcY2qRKaqtpmsT4HKJVfGk+aujg2d69l/PjnXfuu1fsPXDYYBXCshrIqkLq3wMDO3S2+dYgKkzwYG4dt5+/qx5qt8/zbWqqQgYOdHSQ/Q53X5bGTKUz0l8rRn5F584AR/ZtrQ5aaZTDatoMpbCad91y2D9DhmHe7507A3Ttaq8tNDc5VhTr2r2Fo3t/Y6b2rjayYy+JDD2h2H9se72NQZy1gZob7TQ32suuq7x0QiBUq3lYtYIo/x+pCLJuCuAJ3sDZfdI05+wJ4QnewNoS+DdIdfvQe88SHx9mPHzeND9+6xzx8WH0Y2dRdd/KIcPlI5dOkXh4kyYtD0Lg6DiGY38vCEGTlifx8Ca5dAqjBFS2GVIzMdY16PjXujCyadS1zdTvOQpAeuwVfIrh97iwNuikEjG0lUC21nbcB/uYj0bIZxawCEEqHiX1bBAMIPEBmyL4trjAfDSCv/cUX5+GyUyOmnKVLJ2zO4T0bGBy8DKWn51lUwSzj8LMPg5jUwpjihBMDl5Bejbg7A4VzVUSGr5wnGRklLa+00stLLQ6Np+5w+YzdxC2NYWFQtDWd5pkZJThC8erh7yZBNH715BuH0IWqm9IDYtDR2n0YPyEhNSQ7iai967hzSSqhzRVwb+xlcxcknw2DUDu80eGzvcRH3lBbnYGgHw2TXY+ib+lFU1VqocAvsQmUKTE3RNCcXmRioX1i3Fi964iFQuKy4u7J4RQVL7EJpbNUxaSqSQjF4NkVDuOQ/1Lb+pVcwA4DvWTUe28vRRELswum6fsPpKKBW8mwfvrJxAIWvTCd1EtheYYvT6AgUFTg4ZcpmxFIQNMVy1NVdik1xVN8AsuFn8eHabSvZnOFz1bqg0DeD2dX3oWf9+9F9MpcrlcDSiQUqLZC5UwlU6z16GVP8eqjv/vkv8DdXDgFT1RKr8AAAAASUVORK5CYII=";
        const img = Image.fromBase64(base64Img);
        expect(img).instanceOf(Image);
        expect(img.height() > 0).to.equal(true);
        expect(img.width() > 0).to.equal(true);
    });
});