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
    shaders/myShader.frs \
    shaders/myShader.vrs \
    textures/awesome.png \
    textures/container.png



!isEmpty(target.path): INSTALLS += target

OTHER_FILES += \
    $$PWD/textures \
    $$PWD/shaders

# Копирует файлы из директорий в OTHER_FILES в выходную
defineTest(copyToDestDir) {
    files = $$1
    dir = $$2
    # Замена слэшей, если используется Windows
    win32:dir ~= s,/,\\,g

    for(file, files) {
        # Замена слэшей, если используется Windows
        win32:file ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$shell_quote($$file) $$shell_quote($$dir) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

copyToDestDir($$OTHER_FILES, $$OUT_PWD/)
