{
    "targets": [{
        "target_name": "testaddon",
        "cflags!": [ "-fno-rtti","-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "cflags":[ "-std=c++11"],
        "sources": [
            "cppsrc/main.cpp",
	"cppsrc/Samples/functionexample.cpp",
	"cppsrc/Samples/toojpeg.cpp"

        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
	"cppsrc/fc-include"
	
        ],
        'libraries': [
	#"C:\\Users\\BNRI\Desktop\\Project\\Sample-flycapture2\\cppsrc\\fc-lib64\\FlyCapture2_v100.lib"
	"<!@(cd)\cppsrc\\fc-lib64\\FlyCapture2_v100.lib"
        ],
   "copies": [
            {
              "destination": "<(module_root_dir)/build/Release/",
              "files": [  
                       #"<(module_root_dir)/dll/FlyCapture2_v100.dll",
		"<(module_root_dir)/dll/*.*" ]
            }
    ],
    'msvs_settings': {
        'VCCLCompilerTool': {
            'AdditionalOptions': [
                '/GR-',
                '/MT',
                '/EHsc'
            ]
        }
      },
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}