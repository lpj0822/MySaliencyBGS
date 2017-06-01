QT += core
QT -= gui

TARGET = MySaliencyBGS
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(saliencyDetect/saliencyDetect.pri)
include(colorConvert/colorConvert.pri)
include(algorithmBGS/algorithmBGS.pri)
include(imageFiltering/imageFiltering.pri)

SOURCES += main.cpp \
    saliencybgs.cpp \
    dirprocess.cpp \
    performanceanalysis.cpp \
    ivibebgs.cpp \
    tool.cpp

HEADERS += \
    saliencybgs.h \
    dirprocess.h \
    performanceanalysis.h \
    ivibebgs.h \
    tool.h

INCLUDEPATH += D:\opencv\install\include\
               D:\opencv\install\include\opencv\
               D:\opencv\install\include\opencv2


CONFIG(debug,debug|release) {
LIBS += -LD:\opencv\install\x64\vc12\lib \
    -lopencv_aruco310d \
    -lopencv_bgsegm310d \
    -lopencv_bioinspired310d \
    -lopencv_calib3d310d \
    -lopencv_ccalib310d \
    -lopencv_core310d \
    -lopencv_datasets310d \
    -lopencv_dnn310d \
    -lopencv_dpm310d \
    -lopencv_face310d \
    -lopencv_features2d310d \
    -lopencv_flann310d \
    -lopencv_fuzzy310d \
    -lopencv_highgui310d \
    -lopencv_imgcodecs310d \
    -lopencv_imgproc310d \
    -lopencv_line_descriptor310d \
    -lopencv_ml310d \
    -lopencv_objdetect310d \
    -lopencv_optflow310d \
    -lopencv_photo310d \
    -lopencv_plot310d \
    -lopencv_reg310d \
    -lopencv_rgbd310d \
    -lopencv_saliency310d \
    -lopencv_shape310d \
    -lopencv_stereo310d \
    -lopencv_stitching310d \
    -lopencv_structured_light310d \
    -lopencv_superres310d \
    -lopencv_surface_matching310d \
    -lopencv_text310d \
    -lopencv_tracking310d \
    -lopencv_ts310d \
    -lopencv_video310d \
    -lopencv_videoio310d \
    -lopencv_videostab310d \
    -lopencv_xfeatures2d310d \
    -lopencv_ximgproc310d \
    -lopencv_xobjdetect310d \
    -lopencv_xphoto310d
} else {
LIBS += -LD:\opencv\install\x64\vc12\lib \
    -lopencv_aruco310 \
    -lopencv_bgsegm310 \
    -lopencv_bioinspired310 \
    -lopencv_calib3d310 \
    -lopencv_ccalib310 \
    -lopencv_core310 \
    -lopencv_datasets310 \
    -lopencv_dnn310 \
    -lopencv_dpm310 \
    -lopencv_face310 \
    -lopencv_features2d310 \
    -lopencv_flann310 \
    -lopencv_fuzzy310 \
    -lopencv_highgui310 \
    -lopencv_imgcodecs310 \
    -lopencv_imgproc310 \
    -lopencv_line_descriptor310 \
    -lopencv_ml310 \
    -lopencv_objdetect310 \
    -lopencv_optflow310 \
    -lopencv_photo310 \
    -lopencv_plot310 \
    -lopencv_reg310 \
    -lopencv_rgbd310 \
    -lopencv_saliency310 \
    -lopencv_shape310 \
    -lopencv_stereo310 \
    -lopencv_stitching310 \
    -lopencv_structured_light310 \
    -lopencv_superres310 \
    -lopencv_surface_matching310 \
    -lopencv_text310 \
    -lopencv_tracking310 \
    -lopencv_ts310 \
    -lopencv_video310 \
    -lopencv_videoio310 \
    -lopencv_videostab310 \
    -lopencv_xfeatures2d310 \
    -lopencv_ximgproc310 \
    -lopencv_xobjdetect310 \
    -lopencv_xphoto310
}

LIBS +=D:\opencv\install\x64\vc12\staticlib\ippicvmt.lib
