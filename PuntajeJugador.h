#pragma once
#include <string>
class PuntajeJugador
{
private:
	char _nombreJugador[13];
	//std::string _nombreJugador; /// COMO ES DINAMICO NO LO PUEDO GUARDAR EN ARCHIVOS
	int _puntaje;
public:
	PuntajeJugador();
	PuntajeJugador(const std::string& jugador, int puntos);
	const std::string getNombreJugador() const;
	int getPuntaje() const;
	void setNombreJugador(const std::string& jugador);
	void setPuntaje(int puntos);

	// Sobrecarga de operador
	bool operator<(PuntajeJugador aux);
};
