#include "../lib/ControladorTexturas.h"

GLuint ControladorTexturas::texturaEstructuraDestructible = 0;
GLuint ControladorTexturas::texturaEstructuraNoDestructible = 0;
GLuint ControladorTexturas::player = 0;

void ControladorTexturas::cargarTexturas() {
    //CARGAR IMAGEN
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename("texturas/estructura_destructible.jpg");
    FIBITMAP* bitmap = FreeImage_Load(fif, "texturas/estructura_destructible.jpg"); //estoy recibiendo bitmap null
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    int w = FreeImage_GetWidth(bitmap);
    int h = FreeImage_GetHeight(bitmap);
    void* datos = FreeImage_GetBits(bitmap);
    //FIN CARGAR IMAGEN

    GLuint textura;
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, datos);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    ControladorTexturas::texturaEstructuraDestructible = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/estrcutura_no_destructible.png");
    bitmap = FreeImage_Load(fif, "texturas/estrcutura_no_destructible.png"); //estoy reciviendo bitmap null
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    w = FreeImage_GetWidth(bitmap);
    h = FreeImage_GetHeight(bitmap);
    datos = FreeImage_GetBits(bitmap);
    //FIN CARGAR IMAGEN

    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, datos);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    ControladorTexturas::texturaEstructuraNoDestructible = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/Chicken02Col.jpg");
    bitmap = FreeImage_Load(fif, "texturas/Chicken02Col.jpg"); //estoy reciviendo bitmap null
    bitmap = FreeImage_ConvertTo24Bits(bitmap);
    w = FreeImage_GetWidth(bitmap);
    h = FreeImage_GetHeight(bitmap);
    datos = FreeImage_GetBits(bitmap);
    //FIN CARGAR IMAGEN

    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, datos);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    ControladorTexturas::player = textura;
    //FIN TEXTURA
}

GLuint ControladorTexturas::getTextura(tipo_textura tipo) {
    switch (tipo) {
        case ESTRUCTURA_DESTRUCTIBLE:
            return ControladorTexturas::texturaEstructuraDestructible;
            break;
        case ESTRUCTURA_NO_DESTRUCTIBLE:
            return ControladorTexturas::texturaEstructuraNoDestructible;
            break;
        case PLAYER:
            return ControladorTexturas::player;
            break;
        default:
            return 0;
            break;
    }
}