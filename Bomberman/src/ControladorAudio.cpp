#include "../lib/ControladorAudio.h"

ALCdevice* ControladorAudio::openALDevice = nullptr;
ALCcontext* ControladorAudio::openALContext = nullptr;
ALCboolean ControladorAudio::contextMadeCurrent = false;

list<sounds> ControladorAudio::sonidos = list<sounds>();

void ControladorAudio::initOpenAl() {
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

void ControladorAudio::cargarAudios() {
	
	initOpenAl();

	list<ALuint> buffers = list<ALuint>();
	buffers.push_back(bufferAudio::agregarSonido("audio/muerte.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/explosion.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/bonificacion.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/pasos.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/inicioJuego.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/puertaAbierta.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/bomberman.wav"));

	int i = 0;
	for (auto audio = buffers.begin(); audio != buffers.end(); ++audio) {
		sounds sound = {static_cast<sonido>(i),new recursoAudio((*audio)) };
		sonidos.push_back(sound);
		i++;
	}

	while (!buffers.empty()) {
		buffers.pop_back();
	}

}

void ControladorAudio::playAudio(sonido s) {
	if (!mute) {
		boolean encontrado = false;
		for (auto songs = sonidos.begin(); !encontrado && songs != sonidos.end(); ++songs) {
			if (songs->sonido == s) {
				songs->recurso->play();
				encontrado = true;
			}
		}
	}
}

void ControladorAudio::pausarAudio() { //se lo llama cuando se pausa el juego
	if (!mute) {
		for (auto songs = sonidos.begin(); songs != sonidos.end(); ++songs) {
			songs->recurso->pausar();
		}
	}
}

void ControladorAudio::reanudarAudio() { //se lo llama cuando se saca la pausa al juego
	if (!mute) {
		for (auto songs = sonidos.begin(); songs != sonidos.end(); ++songs) {
			songs->recurso->reanudar();
		}
	}
}

void ControladorAudio::detenerAudio() { //creo que ya no usamos el detenerAudio ni el detener
	if (!mute) {
		for (auto songs = sonidos.begin(); songs != sonidos.end(); ++songs) {
			songs->recurso->detener();
		}
	}
	mute = !mute;
}

void ControladorAudio::silenciarAudio() {
	mute = !mute;
	for (auto songs = sonidos.begin(); songs != sonidos.end(); ++songs) {
		songs->recurso->silenciar(mute);
	}
}

//Se deberia controlar las excepciones
void ControladorAudio::limpiarAudios() {
	
	while (!sonidos.empty()) {
		delete sonidos.begin()->recurso;
		sonidos.pop_front();
	}

	bufferAudio::limpiarBuffer();

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(openALContext);
	alcCloseDevice(openALDevice);
}