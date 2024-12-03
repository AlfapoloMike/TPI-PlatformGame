#include "Ayuda.h"
#include <iostream>

Ayuda::Ayuda(){
    if (!_ayudaTexture.loadFromFile("./assets/fondos/fondo.png")) { // Ruta a la imagen de fondo
        std::cout << "Error al cargar fondo Ayuda" << std::endl;
    }
    _ayudaSprite.setTexture(_ayudaTexture); // Asignamos la textura al sprite

    if (!font.loadFromFile("./assets/fonts/Pixelon.ttf")) {
        std::cout << "Error al cargar la fuente" << std::endl;
    }
}

Ayuda::~Ayuda(){

}

void Ayuda::update(){

    _instruccionesTitulo.setFont(font);
    _instruccionesTitulo.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _instruccionesTitulo.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _instruccionesTitulo.setOutlineThickness(5); // Grosor del contorno
    _instruccionesTitulo.setString("INSTRUCCIONES");
    _instruccionesTitulo.setCharacterSize(90);
    _instruccionesTitulo.setFillColor(sf::Color(180, 80, 80, 255));
    _instruccionesTitulo.setPosition(130.0f, 1.0f);
    _instruccionesTituloSombra.setFont(font);
    _instruccionesTituloSombra.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _instruccionesTituloSombra.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _instruccionesTituloSombra.setOutlineThickness(3.f); // Grosor del contorno
    _instruccionesTituloSombra.setOutlineColor(sf::Color(20, 10, 10, 150)); // Color del contorno
    _instruccionesTituloSombra.setString("INSTRUCCIONES");
    _instruccionesTituloSombra.setCharacterSize(90);
    _instruccionesTituloSombra.setFillColor(sf::Color(20, 10, 10, 250));
    _instruccionesTituloSombra.setPosition(140.0f, 40.0f);;

    controles = "CONTROLES:\n\n";
    controles += "  - Movimiento:\n";
    controles += "      Usa las flechas direccionales (o A y D) del teclado para desplazarte hacia la\n";
    controles += "      izquierda y derecha en el aire o por el terreno y plataformas.\n\n";
    controles += "  - Salto:\n";
    controles += "      Presiona la barra espaciadora para saltar y superar obstáculos.\n";
    controles += "      Pulsa nuevamente en el aire para realizar un doble salto.\n";

    _controles.setFont(font);
    _controles.setString(controles);
    _controles.setCharacterSize(18);
    _controles.setFillColor(sf::Color::White);
    //_controles.setFillColor(sf::Color(180, 80, 80, 255)); // ROJIZO
    _controles.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _controles.setOutlineThickness(3); // Grosor del contorno
    _controles.setOutlineColor(sf::Color::Black); // Color del contorno
    _controles.setScale(0.8f, 1.0f);
    _controles.setPosition(70, 150);   
    
    objetivo = "OBJETIVOS:\n\n";
    objetivo += " - Recolecta la mayor cantidad de frutas.\n";
    objetivo += " - Rescata a los aldeanos saltandoles encima\n";
    objetivo += "    para liberarlos del control del hechicero.\n";
    objetivo += " - Derrota al hechicero\n";

    _objetivo.setFont(font);
    _objetivo.setString(objetivo);
    _objetivo.setCharacterSize(18);
    _objetivo.setFillColor(sf::Color::White);
    //_objetivo.setFillColor(sf::Color(180, 80, 80, 255)); // ROJIZO
    _objetivo.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _objetivo.setOutlineThickness(3); // Grosor del contorno
    _objetivo.setOutlineColor(sf::Color::Black); // Color del contorno
    _objetivo.setScale(0.8f, 1.0f);
    _objetivo.setPosition(70, 350);

}

void Ayuda::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(_ayudaSprite, states);
    target.draw(_instruccionesTituloSombra, states);
    target.draw(_instruccionesTitulo, states);
    target.draw(_controles, states);
    target.draw(_objetivo, states);
}
