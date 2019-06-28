#!/usr/bin/env ts-node
import * as nodoface from '../';
let argv = process.argv.slice(2);

let img = nodoface.readImage(argv[0]);
console.log(`Image: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
nodoface.showImage(img, "Show Image");
nodoface.waitKey(0);
img = nodoface.readImage(argv[0], true);
nodoface.showImage(img, 'output', true);
nodoface.waitKey(0);
nodoface.destroyAllWindows();
