#include "../lib/ControladorAudio.h"

ControladorAudio* ControladorAudio::instancia = nullptr;

ControladorAudio* ControladorAudio::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorAudio();
	return instancia;
}

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

ControladorAudio::ControladorAudio() {

	openALDevice = nullptr;
	openALContext = nullptr;
	contextMadeCurrent = false;

	cantFuentesBomba = 4;
	actualBomba = 0;
	actualMecha = 0;
	sonidosBomba = new recursoAudio * [cantFuentesBomba];
	sonidosMecha = new recursoAudio * [cantFuentesBomba];

	initOpenAl();

	list<ALuint> buffers = list<ALuint>();
	buffers.push_back(bufferAudio::agregarSonido("audio/muerte.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/bonificacion.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/pasos.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/inicioJuego.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/puertaAbierta.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/musica.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/timer.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/menu.wav"));
	buffers.push_back(bufferAudio::agregarSonido("audio/muerteEnemigo.wav"));

	int i = 0;
	for (auto audio = buffers.begin(); audio != buffers.end(); ++audio) {
		sounds sound = {static_cast<sonido>(i),new recursoAudio((*audio)) };
		sonidos.push_back(sound);
		if (static_cast<sonido>(i) == sonido::musica)
			sound.recurso->setBucle(true);
		i++;
	}

	while (!buffers.empty()) {
		buffers.pop_back();
	}

	ALuint buf = bufferAudio::agregarSonido("audio/explosion.wav");

	i = 0;
	for (i; i < cantFuentesBomba; i++) {
		sonidosBomba[i] = new recursoAudio(buf);
	}

	buf = bufferAudio::agregarSonido("audio/mecha.wav");

	i = 0;
	for (i; i < cantFuentesBomba; i++) {
		sonidosMecha[i] = new recursoAudio(buf);
	}

}

void ControladorAudio::playBomba(vector_3 pos) {
	if (!mute) {
		sonidosBomba[actualBomba % cantFuentesBomba]->setPosicion(pos.x,pos.y,pos.z);
		sonidosBomba[actualBomba % cantFuentesBomba]->play();
		actualBomba++;
	}
}

int ControladorAudio::playMecha(vector_3 pos) {
	int res = actualMecha;
	if (!mute) {
		sonidosMecha[actualMecha % cantFuentesBomba]->setPosicion(pos.x, pos.y, pos.z);
		sonidosMecha[actualMecha % cantFuentesBomba]->play();
		actualMecha++;
	}
	return res;
}

void ControladorAudio::detenerMecha(int idMecha) {
	sonidosMecha[idMecha % cantFuentesBomba]->detener();
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

void ControladorAudio::playAudio(sonido s, vector_3 pos) {
	if (!mute) {
		boolean encontrado = false;
		for (auto songs = sonidos.begin(); !encontrado && songs != sonidos.end(); ++songs) {
			if (songs->sonido == s) {
				songs->recurso->setPosicion(pos.x, pos.y, pos.z);
				songs->recurso->play();
				encontrado = true;
			}
		}
	}
}

void ControladorAudio::pausarAudio() { //se lo llama cuando se pausa el juego
	if (!mute) {
		for (auto songs = sonidos.begin(); songs != sonidos.end(); ++songs) {
			if (songs->sonido == sonido::musica)
				songs->recurso->silenciar(mute);
			else
				songs->recurso->pausar();
			
		}
		for (int i = 0; i < cantFuentesBomba; i++) {
			sonidosBomba[i]->pausar();
		}
		for (int i = 0; i < cantFuentesBomba; i++) {
			sonidosMecha[i]->pausar();
		}
	}
}

void ControladorAudio::reanudarAudio() { //se lo llama cuando se saca la pausa al juego
	if (!mute) {
		for (auto songs = sonidos.begin(); songs != sonidos.end(); ++songs) {
			if (songs->sonido == sonido::musica)
				songs->recurso->silenciar(mute);
			else
				songs->recurso->reanudar();
		}
		for (int i = 0; i < cantFuentesBomba; i++) {
			sonidosBomba[i]->reanudar();
		}
		for (int i = 0; i < cantFuentesBomba; i++) {
			sonidosMecha[i]->reanudar();
		}
	}
}

void ControladorAudio::detenerAudio() { //creo que ya no usamos el detenerAudio ni el detener
	if (!mute) {
		for (auto songs = sonidos.begin(); songs != sonidos.end(); ++songs) {
			songs->recurso->detener();
		}
		for (int i = 0; i < cantFuentesBomba; i++) {
			sonidosBomba[i]->detener();
		}
		for (int i = 0; i < cantFuentesBomba; i++) {
			sonidosMecha[i]->detener();
		}
	}
	mute = !mute;
}

void ControladorAudio::silenciarAudio() {
	mute = !mute;
	for (auto songs = sonidos.begin(); songs != sonidos.end(); ++songs) {
		songs->recurso->silenciar(mute);
	}
	for (int i = 0; i < cantFuentesBomba; i++) {
		sonidosBomba[i]->silenciar(mute);
	}
	for (int i = 0; i < cantFuentesBomba; i++) {
		sonidosMecha[i]->silenciar(mute);
	}
}

void ControladorAudio::modificarVelocidad(float velocidad) {
	for (auto songs = sonidos.begin(); songs != sonidos.end(); ++songs) {
		songs->recurso->setTono(velocidad);
	}
	for (int i = 0; i < cantFuentesBomba; i++) {
		sonidosBomba[i]->setTono(velocidad);
	}
	for (int i = 0; i < cantFuentesBomba; i++) {
		sonidosMecha[i]->setTono(velocidad);
	}
}

ControladorAudio::~ControladorAudio() {
	while (!sonidos.empty()) {
		delete sonidos.begin()->recurso;
		sonidos.pop_front();
	}

	for (int i = 0; i < cantFuentesBomba; i++) {
		delete sonidosBomba[i];
	}

	for (int i = 0; i < cantFuentesBomba; i++) {
		delete sonidosMecha[i];
	}

	bufferAudio::limpiarBuffer();

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(openALContext);
	alcCloseDevice(openALDevice);
}