#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "PuntajeJugador.h"
#include "PuntajeJugadorArchivo.h"
#include "Intro.h"
#include "Ranking.h"
#include "Creditos.h"
#include "Historia.h"
#include "Ayuda.h"
#include "Resultado.h"


class Menu {
public:
    enum AppState { intro, menu, enter_name, history, instructions, statics, credits, result, quit }; // Estados del MENU
    Menu();
    ~Menu();
    void update(sf::RenderWindow& window, bool& menuSi);
    void draw(sf::RenderWindow& window);
    void manejoEvents(sf::Event& event, bool& menuSi);
    void manejoInputs(sf::Event& event);
    void manejoNameInput(sf::Event& event);
    void setMusica();

    void setState(std::string estado);
    void setResultado(bool gano);
    void setFrutasRecolectadas(int frutas[]);
    std::string getNombreJugador();
    int getPuntajeFinal();
    void resetAll();

private:

    AppState currentState; // Estado actual del MENU
    AppState nextState; // Proximo estado 
    sf::Font font; // Fuente general
    int selectedIndex;
    sf::Text pressText;
    bool cambioEstado = false;
    sf::Clock _clockMenu; // handleInput REVISAR si eliminar o no
    bool _completa = false;
    bool _noComenzar = false;
    sf::Music _enter;
    sf::Music _error;
    sf::Music _musicaFondo;
    sf::Music _letra;
    sf::Music _back;

    // Fondo
    sf::Texture _fondoMenuTexture;
    sf::Sprite _fondoMenuSprite;

    // Selector FROGAR MENU
    sf::Texture _selectorMenuTexture;
    sf::Sprite _selectorMenuSprite;

    sf::Text menuTitulo;
    sf::Text menuTituloSombra;
    std::string menuTituloeText = "AGAINST THE CLOCK";
    sf::Text menuText[5], sombra[5]; // Vectores Text de opciones+sombra
    const int numOptions = 5; // Cantidad de opciones
    std::string options[5] = { "JUGAR", "COMO JUGAR", "RANKING", "CREDITOS", "SALIR" }; // Opciones del menú

    /// INGRESO NOMBRE
    sf::Text nombrePress;
    bool enterPress = false; // Bandera para cambio de estado a historia
    std::string playerName;
    // Fondo
    sf::Texture _fondoNombreTexture;
    sf::Sprite _fondoNombreSprite;

    sf::Text nombreTitulo;
    sf::Text nombreTituloSombra;

    Intro _intro;
    Ranking _ranking;
    Creditos _creditos;
    Historia _historia;
    Ayuda _ayuda;
    Resultado _resultado;
};
