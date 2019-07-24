import * as path from 'path';
import { expect } from 'chai';
import { SequenceCapture, saveImage, showImage, waitKey } from '../';
import { after } from 'mocha';

describe('SequenceCapture', () => {
    let dir = path.join(__dirname, 'samples');
    let sc: SequenceCapture;

    beforeEach(() => {
        sc = new SequenceCapture();
    });
    it('Constructor', () => {
        let sc = new SequenceCapture();
        expect(sc).to.instanceof(SequenceCapture);
    });
    it('.open()', () => {
        let args = [__filename, '-f', path.join(dir, 'single_face.mp4')];
        let success = sc.open(args);
        expect(success).to.equal(true);
        sc.close();
    });
    it('.openVideoFile()', () => {
        let file = path.join(dir, 'single_face.mp4');
        let success = sc.openVideoFile(file);
        expect(success).to.equal(true);
    });
    it('.getProgress()', () => {
        let file = path.join(dir, 'single_face.mp4');
        sc.openVideoFile(file);
        expect(sc.getProgress()).to.equal(0);
    });
    it('.getNextImage()', () => {
        let file = path.join(dir, 'single_face.mp4');
        sc.openVideoFile(file);
        let image = sc.getNextFrame();
        expect(image.channels()).to.equal(3);
        expect(sc.height).to.equal(480);
        expect(sc.width).to.equal(640);
        expect(sc.getProgress()).to.greaterThan(0);
    });
    it('.getGrayFrame', () => {
        let file = path.join(dir, 'single_face.mp4');
        sc.openVideoFile(file);
        let image = sc.getGrayFrame();
        expect(image.channels()).to.equal(1);
    });
    it('Loop all frames', () => {
        let file = path.join(dir, 'single_face.mp4');
        sc.openVideoFile(file);
        for (let i = 0; sc.getProgress() < 1; i++) {
            let frame = sc.getNextFrame();
            saveImage(path.join(__dirname, 'outputs', path.basename(__filename).split('.')[0] + i + '.jpg'), frame);
        }
    });
    after(() => {
        sc.close();
    })
});
