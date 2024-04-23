//Referencia: https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/

#include "../lib/cargadorAudio.h"

int32_t convert_to_int(char* buffer, size_t len) {
    int32_t a = 0;
    //if (endian::native == endian::little)
        memcpy(&a, buffer, len);
    /*else
        for (size_t i = 0; i < len; ++i)
            reinterpret_cast<char*>(&a)[3 - i] = buffer[i];*/
    return a;
}

bool load_wav_file_header(ifstream& file,
    uint8_t& channels,
    int32_t& sampleRate,
    uint8_t& bitsPerSample,
    ALsizei& size) {
    char buffer[4];
    if (!file.is_open())
        return false;

    // the RIFF
    if (!file.read(buffer, 4))
    {
        cerr << "ERROR: could not read RIFF" << endl;
        return false;
    }
    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        cerr << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << endl;
        return false;
    }

    // the size of the file
    if (!file.read(buffer, 4))
    {
        cerr << "ERROR: could not read size of file" << endl;
        return false;
    }

    // the WAVE
    if (!file.read(buffer, 4))
    {
        cerr << "ERROR: could not read WAVE" << endl;
        return false;
    }
    if (strncmp(buffer, "WAVE", 4) != 0)
    {
        cerr << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << endl;
        return false;
    }

    // "fmt/0"
    if (!file.read(buffer, 4))
    {
        cerr << "ERROR: could not read fmt/0" << endl;
        return false;
    }

    // this is always 16, the size of the fmt data chunk
    if (!file.read(buffer, 4))
    {
        cerr << "ERROR: could not read the 16" << endl;
        return false;
    }

    // PCM should be 1?
    if (!file.read(buffer, 2))
    {
        cerr << "ERROR: could not read PCM" << endl;
        return false;
    }

    // the number of channels
    if (!file.read(buffer, 2))
    {
        cerr << "ERROR: could not read number of channels" << endl;
        return false;
    }
    channels = convert_to_int(buffer, 2);

    // sample rate
    if (!file.read(buffer, 4))
    {
        cerr << "ERROR: could not read sample rate" << endl;
        return false;
    }
    sampleRate = convert_to_int(buffer, 4);

    // (sampleRate * bitsPerSample * channels) / 8
    if (!file.read(buffer, 4))
    {
        cerr << "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8" << endl;
        return false;
    }

    // ?? dafaq
    if (!file.read(buffer, 2))
    {
        cerr << "ERROR: could not read dafaq" << endl;
        return false;
    }

    // bitsPerSample
    if (!file.read(buffer, 2))
    {
        cerr << "ERROR: could not read bits per sample" << endl;
        return false;
    }
    bitsPerSample = convert_to_int(buffer, 2);

    // data chunk header "data"
    if (!file.read(buffer, 4))
    {
        cerr << "ERROR: could not read data chunk header" << endl;
        return false;
    }
    if (strncmp(buffer, "data", 4) != 0)
    {
        cerr << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << endl;
        return false;
    }

    // size of data
    if (!file.read(buffer, 4))
    {
        cerr << "ERROR: could not read data size" << endl;
        return false;
    }
    size = convert_to_int(buffer, 4);

    /* cannot be at the end of file */
    if (file.eof())
    {
        cerr << "ERROR: reached EOF on the file" << endl;
        return false;
    }
    if (file.fail())
    {
        cerr << "ERROR: fail state set on the file" << endl;
        return false;
    }

    return true;
}

char* cargadorAudio::load_wav(const string& filename,
    uint8_t& channels,
    int32_t& sampleRate,
    uint8_t& bitsPerSample,
    ALsizei& size) {

    ifstream in(filename, ios::binary);
    if (!in.is_open())
    {
        cerr << "ERROR: Could not open \"" << filename << "\"" << endl;
        return nullptr;
    }
    if (!load_wav_file_header(in, channels, sampleRate, bitsPerSample, size))
    {
        cerr << "ERROR: Could not load wav header of \"" << filename << "\"" << endl;
        return nullptr;
    }

    char* data = new char[size];

    in.read(data, size);

    return data;
}