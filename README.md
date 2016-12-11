# waifu2x-converter-vs2015
This project is forked from https://github.com/tanakamura/waifu2x-converter-cpp

I have add it to a visual studio 2015 project.

Now it can just generate w2xc.dll and this library works correctly with waifu2x-converter_x64.exe which is from http://int.main.jp/files/waifu2x-converter_x64_1130.zip


note:

modelHandler_CUDA.ptx20.h, modelHandler_CUDA.ptx30.h and modelHandler_OpenCL.cl.h are included in modelHandler_CUDA.cpp and modelHandler_OpenCL.cpp, but they do not appear in source files.

How to generate:

for modelHandler_CUDA.ptx20.h, modelHandler_CUDA.ptx30.h

  1.use nvcc tocompile modelHandler_CUDA.cu with argument -gencode=arch=compute_20,code=\"sm_20,compute_20\" and -gencode=arch=compute_30,code=\"sm_30,compute_30\" respectively to generate two different modelHandler_CUDA.ptx, then rename them to modelHandler_CUDA.ptx20 and modelHandler_CUDA.ptx30.
  
  2.
  
  ......to be continue.
