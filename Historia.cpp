#include "Historia.h"
#include <iostream>

Historia::Historia() {

    if (!_historiaTexture.loadFromFile("./assets/fondos/fondo.png")) {
        std::cout << "Error al cargar fondo Historia" << std::endl;
    }
    _historiaSprite.setTexture(_historiaTexture);

    if (!font.loadFromFile("./assets/fonts/Pixelon.ttf")) {
        std::cout << "Error al cargar la fuente" << std::endl;
    }

    //Titulo + sombra
    _historiaTitulo.setFont(font);
    _historiaTitulo.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _historiaTitulo.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _historiaTitulo.setOutlineThickness(5); // Grosor del contorno
    _historiaTitulo.setString("HISTORIA");
    _historiaTitulo.setCharacterSize(90);
    _historiaTitulo.setFillColor(sf::Color(180, 80, 80, 255));
    _historiaTitulo.setPosition(240.0f, 1.0f);
    _historiaTituloSombra.setFont(font);
    _historiaTituloSombra.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _historiaTituloSombra.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _historiaTituloSombra.setOutlineThickness(3.f); // Grosor del contorno
    _historiaTituloSombra.setOutlineColor(sf::Color(20, 10, 10, 150)); // Color del contorno
    _historiaTituloSombra.setString("HISTORIA");
    _historiaTituloSombra.setCharacterSize(90);
    _historiaTituloSombra.setFillColor(sf::Color(20, 10, 10, 250));
    _historiaTituloSombra.setPosition(250.0f, 40.0f);

    _historiaPress.setFont(font);
    _historiaPress.setString("Presiona SPACE para historia completa\nENTER para iniciar  o  ESC para volver");
    _historiaPress.setCharacterSize(20);
    _historiaPress.setOutlineThickness(4); // Grosor del contorno
    _historiaPress.setScale(0.8f, 1.0f);
    _historiaPress.setPosition(100.0f, 550.0f);

    // Historia
    _historia += "En un rincon perdido del mundo, se encuentra la apacible aldea de Caponetuch,\n";
    _historia += "un lugar conocido por su abundancia y tranquilidad. Pero esa calma se rompio\n";
    _historia += "abruptamente una noche cuando un siniestro hechicero irrumpio en el gran alma-\n";
    _historia += "cen del pueblo. Con su poderosa magia, robo las provisiones que sustentaban a los\n";
    _historia += "aldeanos y, lo que es peor, esclavizo a varios de ellos bajo su oscuro control.\n\n";

    _historia += "El hechicero no se detuvo ahi. Abriendo portales magicos, escapo con su botin y sus\n";
    _historia += "nuevos siervos hacia dimensiones desconocidas, dejando tras de si una estela de\n";
    _historia += "caos y grietas temporales. Estas grietas, inestables y peligrosas, son la unica pista\n";
    _historia += "que queda de su rastro.\n\n";

    _historia += "Nuestro protagonista, Frogar, un valiente habitante de la aldea, no puede quedarse\n";
    _historia += "de brazos cruzados. Con una mezcla de determinacion y valentia, decide embarcarse\n";
    _historia += "en una mision crucial: atravesar las grietas temporales, recuperar las provisiones\n";
    _historia += "robadas y liberar a los aldeanos de las garras del hechicero.\n\n";

    _historia += "Pero el tiempo juega en su contra. Las grietas no permaneceran abiertas para\n";
    _historia += "siempre, y cada segundo cuenta. Frogar debera superar desafios inimaginables,\n";
    _historia += "enfrentarse a enemigos poderosos y demostrar que la esperanza de un pueblo\n";
    _historia += "puede prevalecer incluso ante la magia mas oscura.\n\n";

    _historia += "Comienza la aventura! Estas listo para acompañar a Frogar en esta mision epica?";

    _historiaText.setFont(font);
    _historiaText.setFillColor(sf::Color(180, 80, 80, 255)); // Establece el color del texto
    _historiaText.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _historiaText.setOutlineThickness(3); // Grosor del contorno
    _historiaText.setOutlineColor(sf::Color::Black); // Color del contorno
    _historiaText.setScale(0.8f, 1.0f);
    _historiaText.setString(_historia);
    _historiaText.setCharacterSize(20);
    _historiaText.setPosition(45.0f, 100.0f); // Ajustar posición para centrar historia

    storyTextDisplay.setFont(font); // Establecer la fuente
    storyTextDisplay.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    storyTextDisplay.setOutlineThickness(3); // Grosor del contorno
    storyTextDisplay.setOutlineColor(sf::Color::Black); // Color del contorno
    storyTextDisplay.setScale(0.8f, 1.0f);
    storyTextDisplay.setCharacterSize(20); // Ajusta el tamaño de la fuente si es necesario
    storyTextDisplay.setPosition(45.0f, 100.0f); // Posición en la ventana (ajusta según sea necesario)
    //storyTextDisplay.setFillColor(sf::Color(180, 80, 80, 255)); // Color ROJIZO
    storyTextDisplay.setFillColor(sf::Color::White); // Color BLANCO
}

Historia::~Historia() {
}


void Historia::update(bool& _completa, bool& noComenzar) {

    if (!_completa) {

        // Si ha pasado el tiempo suficiente, mostramos la siguiente letra
        if (_clockHistoria.getElapsedTime().asSeconds() >= 0.01f) { // 0.01 <=== velocidad del texto
            // Agregar la siguiente letra a _textoMostrado
            if (_letraActual < _historiaText.getString().getSize()) {
                _textoMostrado += _historiaText.getString()[_letraActual];
                _letraActual++;
                _clockHistoria.restart(); // Reiniciar el reloj para el siguiente intervalo
            }
            else {
                //std::cout << "TERMINO" << std::endl;
                _completa = true; // Hemos llegado al final del texto
                noComenzar = true;// No comienza de nuevo la historia despues de completada
            }
        }
    }
    // ****** Resetea texto o lo autocompleta
    if (_completa) {
        // autocompleta
        if (noComenzar) {
            _textoMostrado = _historia;
            _letraActual = (int)_historia.size();
        }
        // resetea
        else {
            _letraActual = 0;
            _textoMostrado = "";
            _clockHistoria.restart();
            noComenzar = true; // bandera para que no comience historia de nuevo
            _completa = false;
        }
    }

    storyTextDisplay.setString(_textoMostrado); // Texto que se mostrará

}

void Historia::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    target.draw(_historiaSprite, states); // Dibuja fondo
    target.draw(_historiaTituloSombra, states);  // Dibuja sombra del titulo
    target.draw(_historiaTitulo, states);        // Dibuja el título

    // Dibujar solo el texto que ha sido mostrado hasta ahora
    /*sf::Text storyTextDisplay;
    storyTextDisplay.setFont(font); // Establecer la fuente
    storyTextDisplay.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    storyTextDisplay.setOutlineThickness(3); // Grosor del contorno
    storyTextDisplay.setOutlineColor(sf::Color::Black); // Color del contorno
    storyTextDisplay.setScale(0.8f, 1.0f);
    storyTextDisplay.setString(_textoMostrado); // Texto que se mostrará
    storyTextDisplay.setCharacterSize(20); // Ajusta el tamaño de la fuente si es necesario
    storyTextDisplay.setPosition(45.0f, 100.0f); // Posición en la ventana (ajusta según sea necesario)
    //storyTextDisplay.setFillColor(sf::Color(180, 80, 80, 255)); // Color ROJIZO
    storyTextDisplay.setFillColor(sf::Color::White); // Color BLANCO*/
    target.draw(storyTextDisplay, states); // Dibujar el texto de la historia
    target.draw(_historiaPress, states);  // Dibujar los botones o texto adicional si es necesario

}

void Historia::resetAll() {
    _letraActual = 0;
    _historia = "";
}
