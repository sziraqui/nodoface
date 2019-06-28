import * as path from 'path';
import { expect } from 'chai';
import { ImageCapture } from '../';

describe('ImageCapture', () => {
    let dir = path.join(__dirname, 'samples', 'frames');
    let ic: ImageCapture;
    it('Constructor', () => {
        ic = new ImageCapture();
        expect(ic).to.instanceof(ImageCapture);
    });
    it('Single image', () => {
        let args = [__filename, '-f', path.join(dir, 'single_face_01.jpg')];
        ic = new ImageCapture();
        let success = ic.open(args);
        expect(success).to.equal(true);
    });
    it('Flow from directory', () => {
        let args = [__filename, '-fdir', dir];
        ic = new ImageCapture();
        let success = ic.open(args);
        expect(success).to.equal(true);
    });
    it('.openImageFiles()', () => {
        ic = new ImageCapture();
        let files = [path.join(dir, 'single_face_01.jpg'), path.join(dir, 'single_face_05.jpg')]
        let success = ic.openImageFiles(files);
        expect(success).to.equal(true);
    });
    it('.openDirectory()', () => {
        ic = new ImageCapture();
        let success = ic.openDirectory(dir);
        expect(success).to.equal(true);
    });
    it('.getProgress()', () => {
        expect(ic.getProgress()).to.equal(0);
    });
    it('.getNextImage()', () => {
        let image = ic.getNextImage();
        expect(image.channels()).to.equal(3);
        expect(ic.height).to.equal(480);
        expect(ic.width).to.equal(640);
        expect(ic.getProgress()).to.greaterThan(0);
    });
    it('.getGrayFrame', () => {
        let image = ic.getGrayFrame();
        expect(image.channels()).to.equal(1);
    });
});