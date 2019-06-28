import * as path from 'path';
import { expect } from 'chai';
import { SequenceCapture } from '../';

describe('SequenceCapture', () => {
    let dir = path.join(__dirname, 'samples', 'frames');
    let sc: SequenceCapture;
    it('Constructor', () => {
        sc = new SequenceCapture();
        expect(sc).to.instanceof(SequenceCapture);
    });
    it('Single image', () => {
        let args = [__filename, '-f', path.join(dir, 'single_face_01.jpg')];
        sc = new SequenceCapture();
        let success = sc.open(args);
        expect(success).to.equal(true);
    });
    it('.openVideoFile()', () => {
        sc = new SequenceCapture();
        let file = path.join(__dirname, 'samples', 'single_face.mp4')
        let success = sc.openVideoFile(file);
        expect(success).to.equal(true);
    });
    it('.getProgress()', () => {
        expect(sc.getProgress()).to.equal(0);
    });
    it('.getNextImage()', () => {
        let image = sc.getNextFrame();
        expect(image.channels()).to.equal(3);
        expect(sc.height).to.equal(480);
        expect(sc.width).to.equal(640);
        expect(sc.getProgress()).to.greaterThan(0);
    });
    it('.getGrayFrame', () => {
        let image = sc.getGrayFrame();
        expect(image.channels()).to.equal(1);
    });
});