import * as path from 'path';
import { expect } from 'chai';
import { VideoCapture, Image } from '../';

describe('VideoCapture', () => {
    let dir = path.join(__dirname, 'samples');
    let cap: VideoCapture;
    it('Constructor', () => {
        cap = new VideoCapture();
        expect(cap).to.instanceof(VideoCapture);
    });
    it('.open()', () => {
        let file = path.join(dir, 'single_face.mp4');
        cap = new VideoCapture();
        cap.open(file);
        expect(cap.isOpened()).to.equal(true);
    });
    it('.read()', () => {
        let image = cap.read();
        expect(image).to.instanceof(Image);
    });
    it('Loop all frames', () => {
        let image = cap.read();
        while (cap.isOpened() && image instanceof Image) {
            expect(image.channels()).to.equal(3);
            expect(image.type()).to.equal(16);
            image = cap.read();
        }
    });
});
