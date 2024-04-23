//Referencia: https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/
//Se podria remplazar utilizando otra libreria externa, por ejemplo AudioFile

#pragma once

#ifndef CARGADORAUDIO_H
#define CARGADORAUDIO_H

#include "stdint.h"
#include "al.h"
#include <iostream>
#include <fstream>

using namespace std;

class cargadorAudio{
public:
	/*static int32_t convert_to_int(char* buffer, size_t len);

    static bool load_wav_file_header(ifstream& file,
        uint8_t& channels,
        int32_t& sampleRate,
        uint8_t& bitsPerSample,
        ALsizei& size);*/

    static char* load_wav(const string& filename,
        uint8_t& channels,
        int32_t& sampleRate,
        uint8_t& bitsPerSample,
        ALsizei& size);
};

#endif CARGADORAUDIO_H
