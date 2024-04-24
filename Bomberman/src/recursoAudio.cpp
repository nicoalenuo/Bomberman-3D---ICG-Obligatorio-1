#include "../lib/recursoAudio.h"

ALuint recursoAudio::p_Source;
float recursoAudio::p_Pitch = 1.f;
float recursoAudio::p_Gain = 1.f;
float recursoAudio::p_Position[3] = { 10,0,0 };
float recursoAudio::p_Velocity[3] = { 0,0,0 };
bool recursoAudio::p_LoopSound = false;
ALuint recursoAudio::p_Buffer = 0;

void recursoAudio::initRecurso(){
	alGenSources(1, &p_Source);
	alSourcef(p_Source, AL_PITCH, p_Pitch);
	alSourcef(p_Source, AL_GAIN, p_Gain);
	alSource3f(p_Source, AL_POSITION, p_Position[0], p_Position[1], p_Position[2]);
	alSource3f(p_Source, AL_VELOCITY, p_Velocity[0], p_Velocity[1], p_Velocity[2]);
	alSourcei(p_Source, AL_LOOPING, p_LoopSound);
	alSourcei(p_Source, AL_BUFFER, p_Buffer);
}

void recursoAudio::Play(const ALuint buffer_to_play) {
	if (buffer_to_play != p_Buffer)
	{
		p_Buffer = buffer_to_play;
		alSourcei(p_Source, AL_BUFFER, (ALint)p_Buffer);
	}

	alSourcePlay(p_Source);

	ALint state = AL_PLAYING;
	/*while (state == AL_PLAYING && alGetError() == AL_NO_ERROR) {
		alGetSourcei(p_Source, AL_SOURCE_STATE, &state);
	}*/
}