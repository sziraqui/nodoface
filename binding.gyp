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
            'src/jserrors/JSErrors.cpp',
            'src/extras/napiextratypes.cpp',
        ],
        'clfags!': [
            '-fnoexceptions',
        ],
        'cflags_cc!': [
            '-fnoexceptions',
        ],
        'include_dirs': [
            '<!@(node -p "require(\'node-addon-api\').include")',
            '<!@(pkg-config "opencv >= <(cv_version)" --cflags)',
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
        'conditions': [
            [
                'OS=="linux" or OS=="freebsd" or OS=="openbsd" or OS=="solaris" or OS=="aix"',
                {
                    'cflags': [
                        '<!@(pkg-config "opencv >= <(cv_version)" --cflags)',
                        '-Wall'
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