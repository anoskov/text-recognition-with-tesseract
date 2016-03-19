TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/opt/opencv3/include
LIBS += -L/usr/local/opt/opencv3/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

INCLUDEPATH += /usr/local/opt/tesseract/include
LIBS += -L/usr/local/lib -ltesseract

INCLUDEPATH += /usr/local/opt/imagemagick/include/ImageMagick-6
LIBS += -L/usr/local/lib -lMagick++-6.Q16

SOURCES += main.cpp \
    recognition.cpp \
    imgprocessing.cpp

HEADERS += \
    recognition.h \
    imgprocessing.h

DISTFILES += \
    .gitignore
