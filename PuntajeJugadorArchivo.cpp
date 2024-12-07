#include "PuntajeJugadorArchivo.h"
#include <iostream>
#include <cstdio>

PuntajeJugadorArchivo::PuntajeJugadorArchivo() {
}

bool PuntajeJugadorArchivo::grabarMarcador(const PuntajeJugador& puntaje) {

    FILE* pFile;
    //pFile = fopen("prueba.dat", "ab");
    fopen_s(&pFile, _ranking10.c_str(), "ab");
    if (pFile == nullptr) {
        std::cout << "NO SE PUDO LEER - grabarMarcador()" << std::endl;
        return false;
    }
    bool escribio = fwrite(&puntaje, sizeof(PuntajeJugador), 1, pFile); // Se agrega el registro al archivo
    fclose(pFile);

    return escribio;
}



PuntajeJugador PuntajeJugadorArchivo::leerJugador(int pos) {

    FILE* pFile;
    PuntajeJugador puntaje;

    fopen_s(&pFile, _ranking10.c_str(), "rb");
    if (pFile == nullptr) {
        std::cout << "NO SE PUDO LEER - leerJugador()" << std::endl;
        return puntaje;
    }
    // Posicionamos cursor
    fseek(pFile, pos * sizeof(puntaje), SEEK_SET); // UBICAMOS CURSOR - (enlace, cuantoMoverme(bytes), desde el principio SEEK_SET)
    fread(&puntaje, sizeof(puntaje), 1, pFile); // LEE REGISTRO UBICADO SEGUN EL CURSOR Y SE GUARDA EN "puntaje" - sin fseek previo leeria el primer registro
    fclose(pFile);

    return puntaje;
}



bool PuntajeJugadorArchivo::leerTodos(PuntajeJugador registros[], int cantidad) {

    FILE* pFile;
    PuntajeJugador obj;
    bool leyo = false;

    fopen_s(&pFile, _ranking10.c_str(), "rb");
    if (pFile == nullptr) {
        std::cout << "NO SE PUDO LEER - leerTodos()" << std::endl;
        return leyo;
    }
    leyo = fread(registros, sizeof obj, cantidad, pFile); // LEE cantidad DE REGISTROS DESDE EL INICIO DEL ARCHIVO Y LOS GUARDA EN registros[].
    fclose(pFile);

    int tam = cantidadRegistros();

    return leyo;
}



int PuntajeJugadorArchivo::cantidadRegistros() {

    FILE* pFile;

    fopen_s(&pFile, _ranking10.c_str(), "rb");
    if (pFile == nullptr) {
        std::cout << "NO SE PUDO LEER - cantidadRegistros()" << std::endl;
        return -1;
    }
    // Posicionamos el cursor al final del ultimo registro
    fseek(pFile, 0, SEEK_END); // fseeK(enlace, sinMoverse, desde el final SEEK_END)
    int tam = ftell(pFile); // ftell ==> CUENTA CUANTOS BYTES HAY HASTA LA UBICACION DEL CURSOR (segun fseek previo)
    fclose(pFile);

    return tam / sizeof(PuntajeJugador); // retorna el resutado de bytesTotal hasta la ubicacion del cursor / bytes de objeto

}



void PuntajeJugadorArchivo::ordenarRanking() {

    int cantidad = cantidadRegistros();
    PuntajeJugador* ranking = nullptr;

    ranking = new PuntajeJugador[cantidad];

    leerTodos(ranking, cantidad);
    
    // SE ORDENA RANKING POR PUNTAJE
    PuntajeJugador aux;
    for (int i = 0; i < cantidad; i++) {
        for (int j = i + 1; j < cantidad; j++) {
            //if (ranking[i].getPuntaje() < ranking[j].getPuntaje()) {
            if (ranking[i] < ranking[j]) {
                aux = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = aux;
            }
        }
    }

    // LIMITAMOS LA CANTIDAD DE REGISTROS A 10
    FILE* p10;
    fopen_s(&p10, _ranking10.c_str(), "wb");
    if (p10 == nullptr) {
        std::cout << "ERROR DE LECTURA p10 - ordenarRanking()" << std::endl;
        return;
    }
    if (cantidad > 10) {
        
        fwrite(ranking, sizeof(PuntajeJugador), 10, p10); // CREAMOS / REESCRIBIMOS EL ARCHIVO CON 10 REGISTROS ORDENADOS
        fclose(p10);
    }
    else {
        fwrite(ranking, sizeof(PuntajeJugador), cantidad, p10); // CREAMOS / REESCRIBIMOS EL ARCHIVO CON LOS REGISTROS EXISTENTES Y ORDENADOS
        fclose(p10);
    }

    delete[] ranking;
}


