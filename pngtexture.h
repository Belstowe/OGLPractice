#ifndef PNGTEXTURE_H
#define PNGTEXTURE_H

#include <GL/glew.h>

class PNGTexture
{
public:
    PNGTexture(const GLchar *name);
    void bind();
    GLuint texture;

private:
    void init();
    bool load(const GLchar *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
};

#endif // PNGTEXTURE_H
