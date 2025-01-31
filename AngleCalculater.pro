TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += /usr/local/include/opencv4/
LIBS += -L/usr/local/lib
LIBS += -lopencv_core \
        -lopencv_features2d \
        -lopencv_highgui \
        -lopencv_imgcodecs \
        -lopencv_imgproc \
        -lopencv_video \
        -lopencv_videoio \
        -lopencv_calib3d
