#include "Creditos.h"
#include <iostream>

Creditos::Creditos(){

    if (!_creditosTexture.loadFromFile("./assets/fondos/fondo.png")) { // Ruta a la imagen de fondo
        std::cout << "Error al cargar fondo Creditos" << std::endl;
    }
    _creditosSprite.setTexture(_creditosTexture); // Asignamos la textura al sprite

    if (!font.loadFromFile("./assets/fonts/Pixelon.ttf")) {
        std::cout << "Error al cargar la fuente" << std::endl;
    }
}

Creditos::~Creditos()
{
}

void Creditos::update(){   

    // Texto Creditos       
    _creditosTitulo.setFont(font);
    _creditosTitulo.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _creditosTitulo.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _creditosTitulo.setOutlineThickness(5); // Grosor del contorno
    _creditosTitulo.setString("CREDITOS");
    _creditosTitulo.setCharacterSize(90);
    _creditosTitulo.setFillColor(sf::Color(180, 80, 80, 255));
    _creditosTitulo.setPosition(240.0f, 1.0f);
    _creditosTituloSombra.setFont(font);
    _creditosTituloSombra.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _creditosTituloSombra.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _creditosTituloSombra.setOutlineThickness(3.f); // Grosor del contorno
    _creditosTituloSombra.setOutlineColor(sf::Color(20, 10, 10, 150)); // Color del contorno
    _creditosTituloSombra.setString("CREDITOS");
    _creditosTituloSombra.setCharacterSize(90);
    _creditosTituloSombra.setFillColor(sf::Color(20, 10, 10, 250));
    _creditosTituloSombra.setPosition(250.0f, 40.0f);

    _creditos = "GRUPO 17\n";
    _creditos += "Desarrolladores:\n";
    _creditos += "    - Miguel Angel Aguilar\n";
    _creditos += "    - Alejandro Olguera\n\n";
    _creditos += "HERRAMIENTAS UTILIZADAS:\n";
    _creditos += "    - Visual Studio\n";
    _creditos += "    - SFML\n";
    _creditos += "    - Box2d";
    _creditosText.setFont(font);
    _creditosText.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _creditosText.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _creditosText.setOutlineThickness(5); // Grosor del contorno
    _creditosText.setString(_creditos);
    _creditosText.setCharacterSize(30);
    //_creditosText.setFillColor(sf::Color(180, 80, 80, 255)); // ROJIZO
    _creditosText.setFillColor(sf::Color::White); // ROJIZO
    _creditosText.setPosition(100.0f, 150.0f);
}

void Creditos::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(_creditosSprite, states);
    target.draw(_creditosTituloSombra, states);
    target.draw(_creditosTitulo, states);
    target.draw(_creditosText, states);

}

