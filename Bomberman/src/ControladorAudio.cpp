#include "../lib/ControladorAudio.h"

ALCdevice* ControladorAudio::openALDevice = nullptr;
ALCcontext* ControladorAudio::openALContext = nullptr;
ALCboolean ControladorAudio::contextMadeCurrent = false;

ALuint ControladorAudio::bufferMuerte;
ALuint ControladorAudio::bufferExplosion;
ALuint ControladorAudio::bufferBonificacion;
ALuint ControladorAudio::bufferPasos;
ALuint ControladorAudio::bufferInicioJuego;
ALuint ControladorAudio::bufferPuertaAbierta;

ALuint ControladorAudio::bufferMusica;

recursoAudio* ControladorAudio::raMuerte;
recursoAudio* ControladorAudio::raExplosion;
recursoAudio* ControladorAudio::raBonificacion;
recursoAudio* ControladorAudio::raPasos;
recursoAudio* ControladorAudio::raInicioJuego;
recursoAudio* ControladorAudio::raPuertaAbierta;

recursoAudio* ControladorAudio::raMusica;

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

	bufferMuerte = bufferAudio::agregarSonido("audio/muerte.wav");
	bufferExplosion = bufferAudio::agregarSonido("audio/explosion.wav");
	bufferBonificacion = bufferAudio::agregarSonido("audio/bonificacion.wav");
	bufferPasos = bufferAudio::agregarSonido("audio/pasos.wav");
	bufferInicioJuego = bufferAudio::agregarSonido("audio/inicioJuego.wav");
	bufferPuertaAbierta = bufferAudio::agregarSonido("audio/puertaAbierta.wav");

	bufferMusica = bufferAudio::agregarSonido("audio/bomberman.wav");

	raMuerte = new recursoAudio(bufferMuerte);
	raExplosion = new recursoAudio(bufferExplosion);
	raBonificacion = new recursoAudio(bufferBonificacion);
	raPasos = new recursoAudio(bufferPasos);
	raInicioJuego = new recursoAudio(bufferInicioJuego);
	raPuertaAbierta = new recursoAudio(bufferPuertaAbierta);

	raMusica = new recursoAudio(bufferMusica);
	raMusica->setBucle(true);
	raMusica->play();
}

void ControladorAudio::playAudio(sonido s) {
	if (!mute) {
		switch (s) {
			case sonido::muerte:
				raMuerte->play();
				break;
			case sonido::explosion:
				raExplosion->play();
				break;
			case sonido::bonificacion:
				raBonificacion->play();
				break;
			case sonido::pasos:
				raPasos->play();
				break;
			case sonido::inicioJuego:
				raInicioJuego->play();
				break;
			case sonido::puertaAbierta:
				raPuertaAbierta->play();
				break;
			case sonido::musica:
				raMusica->play();
				break;
		}
	}
}

void ControladorAudio::pausarAudio() {
	if (pausa) {
		raMuerte->pausar();
		raExplosion->pausar();
		raBonificacion->pausar();
		raPasos->pausar();
		raInicioJuego->pausar();
		raPuertaAbierta->pausar();

		raMusica->pausar();
	} else {
		raMuerte->reanudar();
		raExplosion->reanudar();
		raBonificacion->reanudar();
		raPasos->reanudar();
		raInicioJuego->reanudar();
		raPuertaAbierta->reanudar();

		raMusica->reanudar();
	}
	
}

void ControladorAudio::reanudarAudio() {
	raMuerte->reanudar();
	raExplosion->reanudar();
	raBonificacion->reanudar();
	raPasos->reanudar();
	raInicioJuego->reanudar();
	raPuertaAbierta->reanudar();

	raMusica->reanudar();
}

void ControladorAudio::detenerAudio() {
	if (!mute) {
		raMuerte->detener();
		raExplosion->detener();
		raBonificacion->detener();
		raPasos->detener();
		raInicioJuego->detener();
		raPuertaAbierta->detener();

		raMusica->pausar();
	} else {
		raMusica->reanudar();

	}
	mute = !mute;
}

//Se deberia controlar las excepciones
void ControladorAudio::limpiarAudios() {
	delete raMuerte;
	delete raExplosion;
	delete raBonificacion;
	delete raPasos;
	delete raInicioJuego;
	delete raPuertaAbierta;
	delete raMusica;

	bufferAudio::limpiarBuffer();
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(openALContext);
	alcCloseDevice(openALDevice);
}