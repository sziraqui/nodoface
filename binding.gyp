#!/usr/bin/env python2
{
    'variables': {
        'module_name': 'nodoface',
        'cv_version': '3.4.0',
        'dlib_version': '19.13',
    },
    'targets': [{
        'target_name': '<(module_name)',
        'sources': [
            'src/main.cpp',
            'src/io/ImageCapture.cpp',
            #'src/io/SequenceCapture.cpp',
            'src/extras/napiextratypes.cpp',
            'src/jserrors/JSErrors.cpp',
        ],
        'clfags!': [
            '-fno-exceptions',
        ],
        'cflags_cc!': [
            "-fno-rtti",
            '-fno-exceptions',
        ],
        'include_dirs': [
            '<!@(node -p "require(\'node-addon-api\').include")',
            '/usr/local/include',
            '/usr/local/include/OpenFace',
            '/usr/local/include/opencv',
            '/usr/local/include/opencv2'
        ],
        'libraries': [
            '-L/usr/local/lib',
            '-Wl,-rpath, /usr/local/lib/libUtilities.a',
            '<!@(pkg-config opencv --libs)'
        ],
        'dependencies': [
            '<!@(node -p "require(\'node-addon-api\').gyp")',
        ],
        'defines': [
            'NAPI_DISABLE_CPP_EXCEPTIONS',
            'NODE_ADDON_API_DISABLE_DEPRECATED',
        ],
        'cflags': [
            '-std=c++11',
            '-fPIC'
        ],
        'conditions': [
            [
                'OS=="linux" or OS=="freebsd" or OS=="openbsd" or OS=="solaris" or OS=="aix"',
                {
                    'cflags+': [
                        '-I/usr/local/include',
                        '-I/usr/local/include/OpenFace',
                        '-I/usr/local/include/opencv',
                        '-I/usr/local/include/opencv2'
                        '-Wall',
                    ]
                }
            ],
            [
            'OS=="mac"',
            {
                'cflags+': [
                    '-fvisibility=hidden'
                ],
                'xcode_settings': {
                    'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
                }
            }],
        ],

    }],
}