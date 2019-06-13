#!/usr/bin/env python2
{
    'variables': {
        'module_name': 'nodoface',
        'cv_version': '3.4.0',
        'dlib_version': '19.13',
        'openface_version': '2.1.0'
    },
    'targets': [{
        'target_name': '<(module_name)',
        'sources': [
            'src/main.cpp',
            'src/io/ImageCapture.cpp',
            #'src/io/SequenceCapture.cpp',
            'src/jserrors/JSErrors.cpp',
        ],
        'clfags!': [
            '-fno-exceptions',
        ],
        'cflags_cc!': [
            '-fno-rtti',
            '-fno-exceptions',
        ],
        'include_dirs': [
            '<!@(node -p "require(\'node-addon-api\').include")',
        ],
        'libraries': [
            '<!@(pkg-config "opencv >= <(cv_version)" --libs)',
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
            '<!@(pkg-config "opencv >= <(cv_version)" --cflags)',
            '-Wall',
        ],
        'conditions': [
            [
                'OS=="linux" or OS=="freebsd" or OS=="openbsd" or OS=="solaris" or OS=="aix"',
                {
                    'cflags+': [
                        '-I/usr/local/include',
                        '-I/usr/local/include/OpenFace',
                    ],
                    'include_dirs+': [
                        '/usr/local/include',
                        '/usr/local/include/OpenFace',
                        '/usr/local/include/opencv',
                    ],
                    'libraries+': [
                        '-L/usr/local/lib',
                        '-lUtilities',
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