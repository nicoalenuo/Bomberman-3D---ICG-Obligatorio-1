#include "../lib/ControladorTexturas.h"

GLuint ControladorTexturas::texturaEstructuraDestructible = 0;
GLuint ControladorTexturas::texturaEstructuraNoDestructible = 0;
GLuint ControladorTexturas::texturaPlayer = 0;
GLuint ControladorTexturas::texturaBomba = 0;
GLuint ControladorTexturas::texturaPuerta = 0;
GLuint ControladorTexturas::texturaAUMENTAR_ALCANCE_BOMBA = 0;
GLuint ControladorTexturas::texturaAUMENTAR_CANTIDAD_BOMBA = 0;
GLuint ControladorTexturas::texturaAUMENTAR_VELOCIDAD = 0;
GLuint ControladorTexturas::texturaBOMBAS_ATRAVIESAN_ESTRUCTURAS = 0;
GLuint ControladorTexturas::texturaINMORTALIDAD = 0;

void ControladorTexturas::cargarTexturas() {
    //CARGAR IMAGEN
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename("texturas/estructura_destructible.jpg");
    FIBITMAP* bitmap = FreeImage_Load(fif, "texturas/estructura_destructible.jpg");
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

    texturaEstructuraDestructible = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/estructura_no_destructible.png");
    bitmap = FreeImage_Load(fif, "texturas/estructura_no_destructible.png");
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

    texturaEstructuraNoDestructible = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/player.png");
    bitmap = FreeImage_Load(fif, "texturas/player.png"); 
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

    texturaPlayer = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/bomba.png");
    bitmap = FreeImage_Load(fif, "texturas/bomba.png");
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

    texturaBomba = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/puerta.png");
    bitmap = FreeImage_Load(fif, "texturas/puerta.png"); 
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

    texturaPuerta = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/aumentar_alcance_bombas.png");
    bitmap = FreeImage_Load(fif, "texturas/aumentar_alcance_bombas.png");
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

    texturaAUMENTAR_ALCANCE_BOMBA = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/aumentar_cantidad_bombas.png");
    bitmap = FreeImage_Load(fif, "texturas/aumentar_cantidad_bombas.png");
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

    texturaAUMENTAR_CANTIDAD_BOMBA = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/aumentar_velocidad.png");
    bitmap = FreeImage_Load(fif, "texturas/aumentar_velocidad.png");
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

    texturaAUMENTAR_VELOCIDAD = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/bombas_atraviesan_estructuras.png");
    bitmap = FreeImage_Load(fif, "texturas/bombas_atraviesan_estructuras.png");
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

    texturaBOMBAS_ATRAVIESAN_ESTRUCTURAS = textura;
    //FIN TEXTURA

    //CARGAR IMAGEN
    fif = FreeImage_GetFIFFromFilename("texturas/inmortalidad.png");
    bitmap = FreeImage_Load(fif, "texturas/inmortalidad.png");
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

    texturaINMORTALIDAD = textura;
    //FIN TEXTURA
}

GLuint ControladorTexturas::getTextura(tipo_textura tipo) {
    switch (tipo) {
        case ESTRUCTURA_DESTRUCTIBLE:
            return texturaEstructuraDestructible;
            break;
        case ESTRUCTURA_NO_DESTRUCTIBLE:
            return texturaEstructuraNoDestructible;
            break;
        case PLAYER:
            return texturaPlayer;
            break;
        case TEXTURA_BOMBA:
            return texturaBomba;
            break;
        case TEXTURA_PUERTA:
            return texturaPuerta;
            break;
        case TEXTURA_AUMENTAR_ALCANCE_BOMBA:
            return texturaAUMENTAR_ALCANCE_BOMBA;
            break;
        case TEXTURA_AUMENTAR_CANTIDAD_BOMBA:
            return texturaAUMENTAR_CANTIDAD_BOMBA;
            break;
        case TEXTURA_AUMENTAR_VELOCIDAD:
            return texturaAUMENTAR_VELOCIDAD;
            break;
        case TEXTURA_BOMBAS_ATRAVIESAN_ESTRUCTURAS:
            return texturaBOMBAS_ATRAVIESAN_ESTRUCTURAS;
            break;
        case TEXTURA_INMORTALIDAD:
            return texturaINMORTALIDAD;
            break;
        default:
            return 0;
            break;
    }
}
