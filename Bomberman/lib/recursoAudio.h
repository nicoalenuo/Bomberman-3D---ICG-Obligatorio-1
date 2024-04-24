#pragma once

#ifndef RECURSOAUDIO_H
#define RECURSOAUDIO_H

#include "al.h"

class recursoAudio{
private:
	static ALuint p_Source;
	static float p_Pitch;
	static float p_Gain;
	static float p_Position[3];
	static float p_Velocity[3];
	static bool p_LoopSound;
	static ALuint p_Buffer;
public:
	static void initRecurso();
	static void Play(const ALuint buffer_to_play);

};

#endif RECURSOAUDIO_H
