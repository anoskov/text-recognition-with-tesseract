TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/opt/opencv3/include
LIBS += -L/usr/local/opt/opencv3/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

INCLUDEPATH += /usr/local/opt/tesseract/include
LIBS += -L/usr/local/lib -ltesseract

SOURCES += main.cpp \
    segment.cpp

HEADERS += \
    segment.h \
    recognition.h

DISTFILES += \
    .gitignore
