TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -mwindows
LIBS += -lopengl32
LIBS += -L$$PWD/../Libraries/include/ -lglew32d

SOURCES += \
        main.cpp \
        shader.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Libraries/GLFW/src/ -lglfw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Libraries/GLFW/src/ -lglfw3d
else:unix: LIBS += -L$$PWD/../Libraries/GLFW/src/ -lglfw3

INCLUDEPATH += $$PWD/../Libraries/GLFW/src
DEPENDPATH += $$PWD/../Libraries/GLFW/src

INCLUDEPATH += $$PWD/../Libraries/include/
HEADERS += \
    ../Libraries/include/GLFW/glfw3.h \
    ../Libraries/include/GLFW/glfw3native.h \
    ../Libraries/include/GL/glew.h \
    shader.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Libraries/GLEW/lib/ -lglew32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Libraries/GLEW/lib/ -lglew32d
else:unix: LIBS += -L$$PWD/../Libraries/GLEW/lib/ -lglew32

INCLUDEPATH += $$PWD/../Libraries/GLEW
DEPENDPATH += $$PWD/../Libraries/GLEW

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Libraries/GLEW/lib/ -llibglew32d.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Libraries/GLEW/lib/ -llibglew32d.dll
else:unix: LIBS += -L$$PWD/../Libraries/GLEW/lib/ -llibglew32d.dll

INCLUDEPATH += $$PWD/../Libraries/GLEW
DEPENDPATH += $$PWD/../Libraries/GLEW

DISTFILES += \
    myShader.frs \
    myShader.vrs
