export class FaceModelParameters {
    constructor(arguments: string[]);
    getModelLocation(): string;
    getMtcnnLocation(): string;
    getHaarLocation(): string;
    getCurrentFdId(): number;
    getCurrentLdId(): number;
}