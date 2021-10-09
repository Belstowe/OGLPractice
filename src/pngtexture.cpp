#include "pngtexture.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <png.h>
using namespace std;

PNGTexture::PNGTexture(const GLchar *name) {
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    bool hasAlpha = false;
    int width, height;
    GLubyte *bufImage;
    if (!this->load(name, width, height, hasAlpha, &bufImage)) {
        cout << "Failed to load PNG image" << endl;
        return;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, width,
                 height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
                 bufImage);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(bufImage);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool PNGTexture::load(const GLchar *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;
    if (fopen_s(&fp, name, "rb"))
        return false;

    // Инициализация png_struct со стандартными методами для обработки исключений stderr и longjump
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     NULL, NULL, NULL);
    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }
    // Выделение памяти под изображение
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }
    // Настройка обработки исключений под метод longjump
    // Такая ошибка может возникнуть при чтении файла png
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return false;
    }
    // Настраиваем чтение из файла
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, sig_read);

    // Непосредственно запись изображения по указателям; STRIP_16 - стандартный, PACKING - использование 8-битной глубины цвета, EXPAND - расширяет цветовую палитру RGB
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);
    // Цветовой тип позволяет определить, используется ли RGB или же RGBA (с доп. атрибутом прозрачности)
    if ((color_type == PNG_COLOR_TYPE_GRAY_ALPHA) || (color_type == PNG_COLOR_TYPE_RGB_ALPHA))
        outHasAlpha = true;
    else
        outHasAlpha = false;
    outWidth = width;
    outHeight = height;

    unsigned row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    *outData = (unsigned char *)malloc(row_bytes * outHeight);
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    // Ввиду того, что ось y в OpenGL перевёрнута, переворачиваем текстуру
    for (int i = 0; i < outHeight; i++) {
        memcpy(*outData + (row_bytes * (height - 1 - i)), row_pointers[i], row_bytes);
    }

    // Освобождаем выделенную память
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    return true;
}

void PNGTexture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->texture);
}
