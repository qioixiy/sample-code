TARGET=ARM make && adb push out/ARM/bin/render / && adb push src/gles/shaders /src/gles/shaders/ && adb shell /render
