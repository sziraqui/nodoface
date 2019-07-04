import * as path from 'path';
import { expect } from 'chai';
import { SequenceCapture } from '../';
import { after } from 'mocha';

describe('SequenceCapture', () => {
    let dir = path.join(__dirname, 'samples');
    let sc: SequenceCapture;
    it('Constructor', () => {
        let sc = new SequenceCapture();
        expect(sc).to.instanceof(SequenceCapture);
    });
    it('.open()', () => {
        let args = [__filename, '-f', path.join(dir, 'single_face.mp4')];
        let sc = new SequenceCapture();
        let success = sc.open(args);
        expect(success).to.equal(true);
        sc.close();
    });
    it('.openVideoFile()', () => {
        sc = new SequenceCapture();
        let file = path.join(dir, 'single_face.mp4');
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
    after(() => {
        sc.close();
    })
});
