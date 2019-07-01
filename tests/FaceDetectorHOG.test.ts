import * as path from 'path';
import { expect } from 'chai';
import { FaceDetectorHOG, readImage } from '../';

describe('FaceDetectorHOG', () => {
    let detector: FaceDetectorHOG;
    it('empty constructor', () => {
        detector = new FaceDetectorHOG();
        expect(detector).to.instanceof(FaceDetectorHOG);
    });
    it('.load()', () => {
        expect(detector.load()).undefined;
    });
    it('.detectFaces(img: Image)', () => {
        let file = path.join(__dirname, 'samples', 'frames', 'single_face_05.jpg');
        let img = readImage(file, true);
        let result = detector.detectFaces(img);
        expect(result.detections).to.instanceof(Array);
        expect(result.detections.length).to.equal(1);
    });
    it('Check detection result', () => {
        let file = path.join(__dirname, 'samples', 'frames', 'single_face_01.jpg');
        let img = readImage(file, true);
        let result = detector.detectFaces(img);
        let bbox = {x:0, y:0, width:0, height:0};
        if(result.detections.length > 0) {
            bbox = result.detections[0];
        }
        const deltaX = bbox.width*0.2;
        const deltaY = bbox.height*0.2;
        expect(bbox.x).to.be.closeTo(146, deltaX);
        expect(bbox.y).to.be.closeTo(227, deltaY);
    });
});