#include "../lib/ControladorAudio.h"

ControladorAudio* ControladorAudio::instancia = nullptr;

ControladorAudio::ControladorAudio() {
	openALDevice = alcOpenDevice(nullptr); //obtengo el dispositivo
	if (!openALDevice) {
		cerr << "Error al inicilizar openAL" << endl;
		exit(1);
	}

	openALContext = alcCreateContext(openALDevice, nullptr); //creo el contexto
	if (!openALContext) {
		cerr << "Error al crear el contexto del audio" << endl;
		exit(1);
	}

	contextMadeCurrent = alcMakeContextCurrent(openALContext); //actulizo el contexto
	if (!contextMadeCurrent || (contextMadeCurrent != ALC_TRUE)) {
		cerr << "Error al actualizar el contexto del audio" << endl;
		exit(1);
	}
}

ControladorAudio* ControladorAudio::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorAudio();

	return instancia;
}

void ControladorAudio::cargarAudios() {
	uint8_t channels;
	int32_t sampleRate;
	uint8_t bitsPerSample;
	ALsizei size;
	char* soundData = cargadorAudio::load_wav("audio/haggle1.wav", channels, sampleRate, bitsPerSample, size);
	if (!soundData){
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

	ALuint source;
	alGenSources( 1, &source);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1.0f);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
	alSourcei(source, AL_BUFFER, buffer);

	alSourcePlay(source);

	ALint state = AL_PLAYING;

	while (state == AL_PLAYING)
	{
		alGetSourcei(source, AL_SOURCE_STATE, &state);
	}

	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
}

ControladorAudio::~ControladorAudio() {
	alcDestroyContext(this->openALContext);
	alcCloseDevice(this->openALDevice);
}