TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32: LIBS += -mwindows -lopengl32
else:unix: LIBS += -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lm

SOURCES += \
        camera.cpp \
        main.cpp \
        ogl_obj/objcube.cpp \
        ogl_obj/oglobj.cpp \
        pngtexture.cpp \
        shader.cpp \
        ogl_obj/objpyramid.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Libraries/lib/GLFW/ -lglfw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Libraries/lib/GLFW/ -lglfw3d
else:unix: LIBS += -L$$PWD/../Libraries/lib/GLFW/ -lglfw3
INCLUDEPATH += $$PWD/../Libraries/lib/GLFW
DEPENDPATH += $$PWD/../Libraries/lib/GLFW

LIBS += -L$$PWD/../Libraries/lib/GLEW/ -lglew32d
INCLUDEPATH += $$PWD/../Libraries/lib/GLEW
DEPENDPATH += $$PWD/../Libraries/lib/GLEW

LIBS += -L$$PWD/../Libraries/lib/zlib/ -lzlib.dll
INCLUDEPATH += $$PWD/../Libraries/lib/zlib
DEPENDPATH += $$PWD/../Libraries/lib/zlib

LIBS += -L$$PWD/../Libraries/lib/png/ -lpng
INCLUDEPATH += $$PWD/../Libraries/lib/png
DEPENDPATH += $$PWD/../Libraries/lib/png



INCLUDEPATH += $$PWD/../Libraries/include/
HEADERS += \
    ../Libraries/include/GLFW/glfw3.h \
    ../Libraries/include/GLFW/glfw3native.h \
    ../Libraries/include/GL/glew.h \
    ../Libraries/include/png.h \
    ../Libraries/include/glm/glm.hpp \
    ../Libraries/include/glm/gtc/matrix_transform.hpp \
    ../Libraries/include/glm/gtc/type_ptr.hpp \
    ogl_obj/objcube.h \
    ogl_obj/objpyramid.h \
    camera.h \
    ogl_obj/oglobj.h \
    pngtexture.h \
    shader.h

DISTFILES += \
    shaders/standardShader.frs \
    shaders/standardShader.vrs \
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
