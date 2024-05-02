#include "../lib/ControladorTexturas.h"
#include <iostream>

map<tipo_textura, GLuint> ControladorTexturas::texturas;

map<tipo_textura, char*> ControladorTexturas::direcciones_texturas = {
    {ESTRUCTURA_DESTRUCTIBLE, "texturas/estructura_destructible.jpg"},
    {ESTRUCTURA_NO_DESTRUCTIBLE, "texturas/estructura_no_destructible.png"},
    {PLAYER, "texturas/player.png"},
    {TEXTURA_BOMBA, "texturas/bomba.png"},
    {TEXTURA_PUERTA, "texturas/puerta.jpg"},
    {TEXTURA_AUMENTAR_ALCANCE_BOMBA, "texturas/aumentar_alcance_bombas.png"},
    {TEXTURA_AUMENTAR_CANTIDAD_BOMBA, "texturas/aumentar_cantidad_bombas.png"},
    {TEXTURA_AUMENTAR_VELOCIDAD, "texturas/aumentar_velocidad.png"},
    {TEXTURA_BOMBAS_ATRAVIESAN_ESTRUCTURAS, "texturas/bombas_atraviesan_estructuras.png"},
    {TEXTURA_INMORTALIDAD, "texturas/inmortalidad.png"},
    {TEXTURA_SUELO, "texturas/suelo.jpg"}
};

void ControladorTexturas::cargarTexturas() {
    FREE_IMAGE_FORMAT fif;
    FIBITMAP* bitmap;
    int w, h;
    void* datos;
    GLuint textura;

    for (pair<const tipo_textura, char*> kv : direcciones_texturas) {
        fif = FreeImage_GetFIFFromFilename(kv.second);
        bitmap = FreeImage_Load(fif, kv.second);
        bitmap = FreeImage_ConvertTo24Bits(bitmap);
        w = FreeImage_GetWidth(bitmap);
        h = FreeImage_GetHeight(bitmap);
        datos = FreeImage_GetBits(bitmap);

        glGenTextures(1, &textura);
        glBindTexture(GL_TEXTURE_2D, textura);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, datos);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        texturas[kv.first] = textura;
    }
}
