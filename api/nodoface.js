const path = require('path');
let nodoface = null;
if (process.env.NODOFACE_BUILD_TYPE_DEBUG) {
    nodoface = require(path.resolve(path.join(__dirname, '..', 'build', 'Debug', 'nodoface.node')));
} else {
    console.log(path.resolve(path.join(__dirname, '..', 'build', 'Release', 'nodoface.node')));
    nodoface = require(path.resolve(path.join(__dirname, '..', 'build', 'Release', 'nodoface.node')));
}

module.exports = nodoface;