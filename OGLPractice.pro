TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -mwindows
LIBS += -lopengl32

SOURCES += \
        main.cpp \
        pngtexture.cpp \
        shader.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Libraries/GLFW/src/ -lglfw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Libraries/GLFW/src/ -lglfw3d
else:unix: LIBS += -L$$PWD/../Libraries/GLFW/src/ -lglfw3
INCLUDEPATH += $$PWD/../Libraries/GLFW/src
DEPENDPATH += $$PWD/../Libraries/GLFW/src

LIBS += -L$$PWD/../Libraries/GLEW/lib/ -lglew32d
INCLUDEPATH += $$PWD/../Libraries/GLEW/lib
DEPENDPATH += $$PWD/../Libraries/GLEW/lib

LIBS += -L$$PWD/../Libraries/zlib/ -lzlib.dll
INCLUDEPATH += $$PWD/../Libraries/zlib
DEPENDPATH += $$PWD/../Libraries/zlib

LIBS += -L$$PWD/../Libraries/png/ -lpng
INCLUDEPATH += $$PWD/../Libraries/png
DEPENDPATH += $$PWD/../Libraries/png



INCLUDEPATH += $$PWD/../Libraries/include/
HEADERS += \
    ../Libraries/include/GLFW/glfw3.h \
    ../Libraries/include/GLFW/glfw3native.h \
    ../Libraries/include/GL/glew.h \
    ../Libraries/include/png.h \
    pngtexture.h \
    shader.h

DISTFILES += \
    myShader.frs \
    myShader.vrs
