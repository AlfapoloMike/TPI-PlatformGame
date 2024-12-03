#include "PuntajeJugador.h"
//#include <cstring>

PuntajeJugador::PuntajeJugador(){	
	strcpy_s(_nombreJugador, sizeof(_nombreJugador), "(vacio)");// Usando strcpy_s para copiar de forma segura
	_puntaje = 0;
}

PuntajeJugador::PuntajeJugador(const std::string& jugador, int puntos){
	setNombreJugador(jugador);
	setPuntaje(puntos);
}

/*const char* PuntajeJugador::getNombreJugador() const {
	return _nombreJugador;
}*/
const std::string PuntajeJugador::getNombreJugador() const {
	return _nombreJugador;
}

int PuntajeJugador::getPuntaje() const{
	return _puntaje;
}

void PuntajeJugador::setNombreJugador(const std::string& jugador){
	//strncpy(_nombreJugador, jugador.c_str(), 10); // c_str() devuelve puntero constante de la heap
	strcpy_s(_nombreJugador, sizeof(_nombreJugador), jugador.c_str());
}

void PuntajeJugador::setPuntaje(int puntos){
	_puntaje = puntos;
}