//                                               
// vspring.h                                    
// VSpring                                      
//                                              
// Created by kimbomm on 2018. 10. 16           
// Copyright 2018 kimbomm. All rights reserved. 
//                                              
 
//static library 
#if _MSC_VER==1800 //Visual Studio 2013 
#    if defined(_WIN64) 
#        if defined(_DEBUG) 
#        else 
#        endif //defined(_DEBUG) 
#    else //x86(Win32) 
#        if defined(_DEBUG) 
#        else 
#        endif //defined(_DEBUG) 
#    endif 
#elif _MSC_VER==1900 //Visual Studio 2015 
#    if defined(_WIN64) 
#pragma comment(lib,"ade.lib") 
#pragma comment(lib,"ippicvmt.lib") 
#        if defined(_DEBUG) 
#pragma comment(lib,"ittnotifyd.lib") 
#pragma comment(lib,"libjasperd.lib") 
#pragma comment(lib,"libjpeg-turbod.lib") 
#pragma comment(lib,"libpngd.lib") 
#pragma comment(lib,"libprotobufd.lib") 
#pragma comment(lib,"libtiffd.lib") 
#pragma comment(lib,"libwebpd.lib") 
#pragma comment(lib,"opencv_world400d.lib") 
#pragma comment(lib,"quircd.lib") 
#pragma comment(lib,"zlibd.lib") 
#        else 
#pragma comment(lib,"ittnotify.lib") 
#pragma comment(lib,"libjasper.lib") 
#pragma comment(lib,"libjpeg-turbo.lib") 
#pragma comment(lib,"libpng.lib") 
#pragma comment(lib,"libprotobuf.lib") 
#pragma comment(lib,"libtiff.lib") 
#pragma comment(lib,"libwebp.lib") 
#pragma comment(lib,"opencv_world400.lib") 
#pragma comment(lib,"quirc.lib") 
#pragma comment(lib,"zlib.lib") 
#        endif //defined(_DEBUG) 
#    else //x86(Win32) 
#        if defined(_DEBUG) 
#        else 
#        endif //defined(_DEBUG) 
#    endif 
#elif _MSC_VER //Visual Studio 2017 
#    if defined(_WIN64) 
#        if defined(_DEBUG) 
#        else 
#        endif //defined(_DEBUG) 
#    else //x86(Win32) 
#        if defined(_DEBUG) 
#        else 
#        endif //defined(_DEBUG) 
#    endif 
#endif //_MSC_VER 
 
//shared library 
#if defined(_WIN64) 
#    if defined(_DEBUG) 
#    else 
#    endif //defined(_DEBUG) 
#else //x86(Win32) 
#    if defined(_DEBUG) 
#   else 
#    endif //defined(_DEBUG) 
#endif 
