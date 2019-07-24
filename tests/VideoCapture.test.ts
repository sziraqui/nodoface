import * as path from 'path';
import { expect } from 'chai';
import { VideoCapture, Image, showImage, waitKey, saveImage } from '../';

describe('VideoCapture', () => {
    let dir = path.join(__dirname, 'samples');
    let cap: VideoCapture;
    let file = path.join(dir, 'single_face.mp4');
    beforeEach(() => {
        cap = new VideoCapture();
        cap.open(file);
    });
    it('Constructor', () => {
        cap = new VideoCapture();
        expect(cap).to.instanceof(VideoCapture);
    });
    it('.open()', () => {
        cap.open(file);
        expect(cap.isOpened()).to.equal(true);
    });
    it('.read()', () => {
        expect(cap.isOpened()).to.equal(true);
        let image = cap.read();
        expect(image).to.instanceof(Image);
    });
    it('Loop all frames', () => {
        expect(cap.isOpened()).to.equal(true);
        for (let i = 0; i < 255; i++) {
            let image = cap.read();
            expect(cap.isOpened()).to.equal(true);
            expect(image.channels()).to.equal(3);
            expect(image.type()).to.equal(16);
            let mat = new Image(image.toUint8Array(), image.height(), image.width(), image.type());
            expect(image.toUint8Array()).to.eql(mat.toUint8Array());
            saveImage(path.join(__dirname, 'outputs', path.basename(__filename).split('.')[0] + i + '.jpg'), image);
        }
    });
});
