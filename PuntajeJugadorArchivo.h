#pragma once
#include "PuntajeJugador.h"

/*
fopen() - ABRIR UN ARCHIVVO (CREA UN ENLACE)
	ab - append(AGREGAR) ---> cursor al final
	rb - read(LEER) ---> crusor al principio
	wb - write(ESCRIBE-SOBREESCRIBE)

fwrite() - LO ESCRIBE
fread() - LO LEE
fclose() - LO CIERRA

	FILE *pFile;
	pFile = fopen("algo.dat", )
*/
class PuntajeJugadorArchivo {
private:
	std::string _ranking10 = "ranking10.dat";

public:
	PuntajeJugadorArchivo();
	bool grabarMarcador(const PuntajeJugador& obj);
	PuntajeJugador leerJugador(int pos);
	bool leerTodos(PuntajeJugador registros[], int cantidad);
	int cantidadRegistros();
	void ordenarRanking();
};