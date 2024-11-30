#pragma once
#include "Intro.h"
#include <iostream>

Intro::Intro() {
    opacidad = 0;
    _rutaImagen = "./assets/fondos/introUTN.png";
    if (!_introTexture.loadFromFile(_rutaImagen)) {
        std::cout << "Error al cargar la imagen de INTRO" << std::endl;
    }
    _introSprite.setTexture(_introTexture);

    if (!_introMusic.openFromFile("./assets/audios/PolyStation.wav")) {
        std::cout << "Error al cargar la música de la intro" << std::endl;
    }
}
Intro::~Intro()
{
}

void Intro::update(bool &cambioEstado){

    // Lógica de fade-in y fade-out
    if (fadeOn) {

        opacidad += 1.0f; // Incrementa la transparencia
        if (opacidad >= 255.0f) {

            opacidad = 255.0f; // Limita la transparencia
            fadeOn = false; // Cambia a fade-out
        }
    }
    else {
        opacidad -= 1.0f; // Reduce la transparencia
        if (opacidad <= 0.0f) {
            opacidad = 0.0f; // Evita valores negativos
            cambioEstado = true;
        }
    }

    _introSprite.setColor(sf::Color(255, 255, 255, (int)opacidad)); // Aplica transparencia
}

void Intro::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(_introSprite, states);
}


