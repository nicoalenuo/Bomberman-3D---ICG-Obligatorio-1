#include "../lib/ControladorTexturas.h"

GLuint ControladorTexturas::texturaEstructuraDestructible = 0;
GLuint ControladorTexturas::texturaEstructuraNoDestructible = 0;

void ControladorTexturas::cargarTexturas() {
    //TEXTURA
    const char* archivo1 = "../Bomberman/texturas/estructuraTrue.jpg"; //sacar
    //CARGAR IMAGEN
    FREE_IMAGE_FORMAT fif1 = FreeImage_GetFIFFromFilename(archivo1);
    FIBITMAP* bitmap1 = FreeImage_Load(fif1, archivo1); //estoy recibiendo bitmap null
    bitmap1 = FreeImage_ConvertTo24Bits(bitmap1);
    int w1 = FreeImage_GetWidth(bitmap1);
    int h1 = FreeImage_GetHeight(bitmap1);
    void* datos1 = FreeImage_GetBits(bitmap1);
    //FIN CARGAR IMAGEN

    GLuint textura1;
    glGenTextures(1, &textura1);
    glBindTexture(GL_TEXTURE_2D, textura1);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w1, h1, 0, GL_BGR, GL_UNSIGNED_BYTE, datos1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //FIN TEXTURA

    ControladorTexturas::texturaEstructuraDestructible = textura1;

    //TEXTURA
    const char* archivo2 = "../Bomberman/texturas/estructuraFalse.png"; //sacar

    //CARGAR IMAGEN
    FREE_IMAGE_FORMAT fif2 = FreeImage_GetFIFFromFilename(archivo2);
    FIBITMAP* bitmap2 = FreeImage_Load(fif2, archivo2); //estoy reciviendo bitmap null
    bitmap2 = FreeImage_ConvertTo24Bits(bitmap2);
    int w2 = FreeImage_GetWidth(bitmap2);
    int h2 = FreeImage_GetHeight(bitmap2);
    void* datos2 = FreeImage_GetBits(bitmap2);
    //FIN CARGAR IMAGEN

    GLuint textura2;
    glGenTextures(1, &textura2);
    glBindTexture(GL_TEXTURE_2D, textura2);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w2, h2, 0, GL_BGR, GL_UNSIGNED_BYTE, datos2);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    ControladorTexturas::texturaEstructuraNoDestructible = textura2;
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
        default:
            return 0;
            break;
    }
}
