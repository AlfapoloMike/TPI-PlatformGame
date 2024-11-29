#include <iostream>
#include "Ranking.h"
//#include "PuntajeJugadorArchivo.h"
//#include "PuntajeJugador.h"


Ranking::Ranking(){
    // Fondo
    if (!_rankingTexture.loadFromFile("./assets/fondos/fondo.png")) { // Ruta a la imagen de fondo
        std::cout << "Error al cargar fondo ranking" << std::endl;
    }
    _rankingSprite.setTexture(_rankingTexture); // Asignamos la textura al sprite

    if (!font.loadFromFile("./assets/fonts/Pixelon.ttf")) {
        std::cout << "Error al cargar la fuente" << std::endl;
    }

    // Titulo + Sombra
    _rankingTitulo.setFont(font);
    _rankingTitulo.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _rankingTitulo.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _rankingTitulo.setOutlineThickness(5); // Grosor del contorno
    _rankingTitulo.setString("RANKING GENERAL");
    _rankingTitulo.setCharacterSize(90);
    _rankingTitulo.setFillColor(sf::Color(180, 80, 80, 255));
    _rankingTitulo.setPosition(105.0f, 1.0f);
    _rankingTituloSombra.setFont(font);
    _rankingTituloSombra.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _rankingTituloSombra.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _rankingTituloSombra.setOutlineThickness(3.f); // Grosor del contorno
    _rankingTituloSombra.setOutlineColor(sf::Color(20, 10, 10, 150)); // Color del contorno
    _rankingTituloSombra.setString("RANKING GENERAL");
    _rankingTituloSombra.setCharacterSize(90);
    _rankingTituloSombra.setFillColor(sf::Color(20, 10, 10, 250));
    _rankingTituloSombra.setPosition(115.0f, 40.0f);

    
}


Ranking::~Ranking()
{
}

void Ranking::update(bool& cambioEstado){

    //std::cout << "DESDE Ranking.Update()" << std::endl;
    //PuntajeJugadorArchivo archivo;
    //PuntajeJugador top[5];
    //std::string players = "";
    //std::string scores = "";
    //players = "";
    //scores = "";

    archivo.leerTodos(top, 5);

    _puntajesText.setFont(font);
    _puntajesText.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _puntajesText.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _puntajesText.setOutlineThickness(5); // Grosor del contorno
    _jugadoresText = _puntajesText;



    players = "1. " + top[0].getNombreJugador();
    scores = std::to_string(top[0].getPuntaje());

    players += "\n2. " + top[1].getNombreJugador();
    scores += "\n" + std::to_string(top[1].getPuntaje());

    players += "\n3. " + top[2].getNombreJugador();
    scores += "\n" + std::to_string(top[2].getPuntaje());

    players += "\n4. " + top[3].getNombreJugador();
    scores += "\n" + std::to_string(top[3].getPuntaje());

    players += "\n5. " + top[4].getNombreJugador();
    scores += "\n" + std::to_string(top[4].getPuntaje());

    
    //playersText.setFillColor(sf::Color(180, 80, 80, 255)); // ROJIZO
    _jugadoresText.setFillColor(sf::Color::White);
    _jugadoresText.setCharacterSize(40);
    _puntajesText = _jugadoresText;

    _jugadoresText.setString(players);
    _jugadoresText.setPosition(200.0f, 225.0f);  // Posición de los nombres
    _puntajesText.setString(scores);
    _puntajesText.setPosition(520.0f, 225.0f);  // Posición de los puntajes
}

void Ranking::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    target.draw(_rankingSprite, states); // Dibujar FONDO
    target.draw(_rankingTituloSombra, states);
    target.draw(_rankingTitulo, states);
    target.draw(_jugadoresText, states);  // Dibujar JUGADORES
    target.draw(_puntajesText, states);  // Dibujar PUNTAJES

    //window.draw(pressText);
}


