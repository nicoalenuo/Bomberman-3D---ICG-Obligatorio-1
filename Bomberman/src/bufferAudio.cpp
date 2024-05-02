#include "../lib/bufferAudio.h"

vector<ALuint> bufferAudio::bufferSonidos = {};

ALuint bufferAudio::agregarSonido(const char* filename) {
	uint8_t channels;
	int32_t sampleRate;
	uint8_t bitsPerSample;
	ALsizei size;
	char* soundData = cargadorAudio::load_wav(filename, channels, sampleRate, bitsPerSample, size);
	if (!soundData) {
		cerr << "Error al cargar el audio bounce" << endl;
		exit(1);
	}

	ALuint buffer;
	alGenBuffers(1, &buffer);

	ALenum format;
	if (channels == 1 && bitsPerSample == 8)
		format = AL_FORMAT_MONO8;
	else if (channels == 1 && bitsPerSample == 16)
		format = AL_FORMAT_MONO16;
	else if (channels == 2 && bitsPerSample == 8)
		format = AL_FORMAT_STEREO8;
	else if (channels == 2 && bitsPerSample == 16)
		format = AL_FORMAT_STEREO16;
	else {
		cerr << "Error al reconocer el formato wave de " << channels << " channels, " << bitsPerSample << " bps" << endl;
		exit(1);
	}

	alBufferData(buffer, format, soundData, size, sampleRate);

	bufferSonidos.push_back(buffer);

	return buffer;
}

void bufferAudio::limpiarBuffer() {
	for (size_t i = 0; i < bufferSonidos.size(); i++) {
		alDeleteBuffers(1, &bufferSonidos[i]);
	}
	bufferSonidos.clear();
}

