#include "Resultado.h"
#include <iostream>

Resultado::Resultado(){
    
    // FONDO
    if (!_resultadoTexture.loadFromFile("./assets/fondos/fondo.png")) { // Ruta a la imagen de fondo
        std::cout << "Error al cargar fondo Resultado" << std::endl;
    }
    _resultadoSprite.setTexture(_resultadoTexture); // Asignamos la textura al sprite

    // FUENTE
    if (!font.loadFromFile("./assets/fonts/Pixelon.ttf")) {
        std::cout << "Error al cargar la fuente Resultado" << std::endl;
    }
    // AUDIOS
    if (!conteoPuntos.openFromFile("./assets/audios/conteopuntos.mp3")) {
        std::cout << "Error al cargar audio Resultado - conteoPuntos ";
    }
    //if (!gameover.openFromFile("./assets/audios/gameover.mp3")) {
    //    std::cout << "Error al cargar audio Resultado - gameover ";
    //}
    // ESPACIOS SEPARADORES
    for (int i = 0; i < 8; i++) {
        espacioCant[i] = "            ";
        espacioPuntos[i] = "           ";
    }
    // SOBREFONDO para oscurecer el fondo regulando opacidad OPCIONAL
    //tapaFondo.setSize(sf::Vector2f(800, 600));
    //tapaFondo.setFillColor(sf::Color( 0, 0, 0, 0));
}

Resultado::~Resultado(){
    
}


void Resultado::update(){

    if(counter > 0){
        counter-= 1.30f;
    }
    else {
        counter = 0;
    }

    if (gano) {
        if (gameover.getStatus() != sf::Music::Playing && !gameoverPlayed) {
            if (!gameover.openFromFile("./assets/audios/frogarwin.mp3")) {
                std::cout << "Error al cargar audio Resultado - frogarwin ";
            }
            gameover.play();
            gameoverPlayed = true;
        }
        resultado = "VICTORIA";
        _resultadoTitulo.setPosition(240.0f, 1.0f + counter);
        _resultadoTituloSombra.setPosition(250.0f, 40.0f + counter);
    }
    else {
        if (gameover.getStatus() != sf::Music::Playing && !gameoverPlayed) {
            if (!gameover.openFromFile("./assets/audios/gameover.mp3")) {
                std::cout << "Error al cargar audio Resultado - gameover ";
            }
            gameover.play();
            gameoverPlayed = true;
        }
        // FONDO PERDISTE - Actualizamos fondo o regulamos opacidad de tapaFondo(shape negro)
        if (!_resultadoTexture.loadFromFile("./assets/fondos/fondoperdio.png")) { // Ruta a la imagen de fondo
            std::cout << "Error al cargar fondo Resultado" << std::endl;
        }
        //tapaFondo.setFillColor(sf::Color(0, 0, 0, 200));

        _resultadoSprite.setTexture(_resultadoTexture); // Asignamos la textura al sprite
        resultado = "GAME OVER";
        _resultadoTitulo.setPosition(205.0f, 1.0f + counter);
        _resultadoTituloSombra.setPosition(215.0f, 40.0f + counter);
    }

    
    _resultadoTitulo.setFont(font);
    _resultadoTitulo.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _resultadoTitulo.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _resultadoTitulo.setOutlineThickness(5); // Grosor del contorno
    _resultadoTitulo.setString(resultado);
    _resultadoTitulo.setCharacterSize(90);
    _resultadoTitulo.setFillColor(sf::Color(180, 80, 80, 255));
    
    _resultadoTituloSombra.setFont(font);
    _resultadoTituloSombra.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
    _resultadoTituloSombra.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
    _resultadoTituloSombra.setOutlineThickness(3.f); // Grosor del contorno
    _resultadoTituloSombra.setOutlineColor(sf::Color(20, 10, 10, 150)); // Color del contorno
    _resultadoTituloSombra.setString(resultado);
    _resultadoTituloSombra.setCharacterSize(90);
    _resultadoTituloSombra.setFillColor(sf::Color(20, 10, 10, 250));

    if (counter == 0) {
        _frutasText.setFont(font);
        _frutasText.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
        _frutasText.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
        _frutasText.setOutlineThickness(5); // Grosor del contorno
        _cantidadFrutaText = _frutasText;


        /// CONTEO PUNTOS x Fruta recolectada para MARCADOR
        // Manzana
        if(contadores[0] < cantidades[0] && !contada[0]) {
        
            contadores[0]++;
            puntosFruta[0] = (contadores[0] * 100);

            if (puntosFruta[0] < 10) {
                espacioPuntos[0] = "           ";
            }
            else if (puntosFruta[0] < 100) {
                espacioPuntos[0] = "         ";

            }
            else if (puntosFruta[0] < 1000) {
                espacioPuntos[0] = "       ";
            }
            else {
                espacioPuntos[0] = "      ";
            }

            if (contadores[0] < 10) {
                espacioCant[0] = "            ";
            }
            else {
                espacioCant[0] = "           ";
            }

            if (contadores[0] == cantidades[0]) {
                contada[0] = true;
                conteoPuntos.stop();
            }
        }
        // Banana
        else if (contadores[1] < cantidades[1] && !contada[1]) {
            contadores[1]++;
            puntosFruta[1] = (contadores[1] * 50);

            if (puntosFruta[1] < 10) {
                espacioPuntos[1] = "           ";
            }
            else if (puntosFruta[1] < 100) {
                espacioPuntos[1] = "         ";

            }
            else if (puntosFruta[1] < 1000) {
                espacioPuntos[1] = "       ";
            }
            else {
                espacioPuntos[1] = "      ";
            }

            if (contadores[1] < 10) {
                espacioCant[1] = "            ";
            }
            else {
                espacioCant[1] = "           ";
            }

            if (contadores[1] == cantidades[1]) {
                contada[1] = true;
                conteoPuntos.stop();
            }
        }
        // Frutilla
        else if (contadores[2] < cantidades[2] && !contada[2]) {
            contadores[2]++;
            puntosFruta[2] = (contadores[2] * 150);

            if (puntosFruta[2] < 10) {
                espacioPuntos[2] = "           ";
            }
            else if (puntosFruta[2] < 100) {
                espacioPuntos[2] = "         ";

            }
            else if (puntosFruta[2] < 1000) {
                espacioPuntos[2] = "       ";
            }
            else {
                espacioPuntos[2] = "      ";
            }

            if (contadores[2] < 10) {
                espacioCant[2] = "            ";
            }
            else {
                espacioCant[2] = "           ";
            }
            if (contadores[2] == cantidades[2]) {
                contada[2] = true;
                conteoPuntos.stop();
            }
        }
        //Kiwi
        else if (contadores[3] < cantidades[3] && !contada[3]) {
            contadores[3]++;
            puntosFruta[3] = (contadores[3] * 70);

            if (puntosFruta[3] < 10) {            
                espacioPuntos[3] = "           ";
            }
            else if (puntosFruta[3] < 100) {
                espacioPuntos[3] = "         ";
            
            }
            else if (puntosFruta[3] < 1000) {
                espacioPuntos[3] = "       ";
            }
            else {
                espacioPuntos[3] = "      ";
            }

            if (contadores[3] < 10) {
                espacioCant[3] = "            ";
            }
            else {
                espacioCant[3] = "           ";
            }

            if (contadores[3] == cantidades[3]) {
                contada[3] = true;
                conteoPuntos.stop();
            }
        }
        // Naranaja
        else if (contadores[4] < cantidades[4] && !contada[4]) {
            contadores[4]++;
            puntosFruta[4] = (contadores[4] * 30);

            if (puntosFruta[4] < 10) {
                espacioPuntos[4] = "           ";
            }
            else if (puntosFruta[4] < 100) {
                espacioPuntos[4] = "         ";

            }
            else if (puntosFruta[4] < 1000) {
                espacioPuntos[4] = "       ";
            }
            else {
                espacioPuntos[4] = "      ";
            }

            if (contadores[4] < 10 && puntosFruta[4] < 1000) {
                espacioCant[4] = "            ";
            }
            else {
                espacioCant[4] = "           ";
            }
            if (contadores[4] == cantidades[4]) {
                contada[4] = true;
                conteoPuntos.stop();
            }
        }
        // Cereza
        else if (contadores[5] < cantidades[5] && !contada[5]) {
            contadores[5]++;
            puntosFruta[5] = (contadores[5] * 30);

            if (puntosFruta[5] < 10) {
                espacioPuntos[5] = "           ";
            }
            else if (puntosFruta[5] < 100) {
                espacioPuntos[5] = "         ";
            }
            else if (puntosFruta[5] < 1000) {
                espacioPuntos[5] = "       ";
            }
            else {
                espacioPuntos[5] = "      ";
            }

            if (contadores[5] < 10) {
                espacioCant[5] = "            ";
            }
            else {
                espacioCant[5] = "           ";
            }
            if (contadores[5] == cantidades[5]) {
                contada[5] = true;
                conteoPuntos.stop();
            }
        }
        // Anana
        else if (contadores[6] < cantidades[6] && !contada[6]) {
            contadores[6]++;
            puntosFruta[6] = (contadores[6] * 70);

            if (puntosFruta[6] < 10) {
                espacioPuntos[6] = "           ";
            }
            else if (puntosFruta[6] < 100) {
                espacioPuntos[6] = "         ";
            }
            else if (puntosFruta[6] < 1000) {
                espacioPuntos[6] = "       ";
            }
            else {
                espacioPuntos[6] = "      ";
            }

            if (contadores[6] < 10) {
                espacioCant[6] = "            ";
            }
            else {
                espacioCant[6] = "           ";
            }
            if (contadores[6] == cantidades[6]) {
                contada[6] = true;
                conteoPuntos.stop();
            }
        }
        // Melon
        else if (contadores[7] < cantidades[7] && !contada[7]) {
            contadores[7]++;
            puntosFruta[7] = (contadores[7] * 110); 

            if (puntosFruta[7] < 10) {
                espacioPuntos[7] = "           ";
            }
            else if (puntosFruta[7] < 100) {
                espacioPuntos[7] = "         ";

            }
            else if (puntosFruta[7] < 1000) {
                espacioPuntos[7] = "       ";
            }
            else {
                espacioPuntos[7] = "      ";
            }

            if (contadores[7] < 10) {
                espacioCant[7] = "            ";
            }
            else {
                espacioCant[7] = "           ";
            }
            if (contadores[7] == cantidades[7]) {
                contada[7] = true;
                conteoPuntos.stop();
            }
        }

        // Sonidito
        if (conteoPuntos.getStatus() != sf::Music::Playing
            && !contada[7]) {
            conteoPuntos.play();
        }

        // Acumulando para marcador
        puntosTotal = puntosFruta[0] + puntosFruta[1] + puntosFruta[2] + puntosFruta[3] + puntosFruta[4] + puntosFruta[5] + puntosFruta[6] + puntosFruta[7];
        cantidadTotal = contadores[0] + contadores[1] + contadores[2] + contadores[3] + contadores[4] + contadores[5] + contadores[6] + contadores[7];

        frutas = "FRUTAS\n";
        cantFrutas = "CANTIDAD\n";
        puntosFrutas = "PUNTAJE\n";

        frutas += "\nManzanas";
        cantFrutas += "\n" + espacioCant[0] + std::to_string(contadores[0]);
        puntosFrutas += "\n" + espacioPuntos[0] + std::to_string(puntosFruta[0]);

        frutas += "\n\nBanana";
        cantFrutas += "\n\n" + espacioCant[1] + std::to_string(contadores[1]);
        puntosFrutas += "\n\n" + espacioPuntos[1] + std::to_string(puntosFruta[1]);

        frutas += "\n\nFrutilla";
        cantFrutas += "\n\n" + espacioCant[2] + std::to_string(contadores[2]);
        puntosFrutas += "\n\n" + espacioPuntos[2] + std::to_string(puntosFruta[2]);

        frutas += "\n\nKiwi";
        cantFrutas += "\n\n" + espacioCant[3] + std::to_string(contadores[3]);
        puntosFrutas += "\n\n" + espacioPuntos[3] + std::to_string(puntosFruta[3]);

        frutas += "\n\nNaranja";
        cantFrutas += "\n\n" + espacioCant[4] + std::to_string(contadores[4]);
        puntosFrutas += "\n\n" + espacioPuntos[4] + std::to_string(puntosFruta[4]);

        frutas += "\n\nCereza";
        cantFrutas += "\n\n" + espacioCant[5] + std::to_string(contadores[5]);
        puntosFrutas += "\n\n" + espacioPuntos[5] + std::to_string(puntosFruta[5]);

        frutas += "\n\nAnana";
        cantFrutas += "\n\n" + espacioCant[6] + std::to_string(contadores[6]);
        puntosFrutas += "\n\n" + espacioPuntos[6] + std::to_string(puntosFruta[6]);

        frutas += "\n\nMelon";
        cantFrutas += "\n\n" + espacioCant[7] + std::to_string(contadores[7]);
        puntosFrutas += "\n\n" + espacioPuntos[7] + std::to_string(puntosFruta[7]);

    

        frutas += "\n\nTOTAL OBTENIDO";
        cantFrutas += "\n\n          " + std::to_string(cantidadTotal);
        puntosFrutas += "\n\n     " + std::to_string(puntosTotal);


        _frutasText.setFillColor(sf::Color::White);
        _frutasText.setCharacterSize(20);
        _puntajesFrutasText = _cantidadFrutaText = _frutasText;

        _frutasText.setString(frutas);
        _frutasText.setPosition(190.0f, 140.0f);  // Posici�n de frutas
        _cantidadFrutaText.setString(cantFrutas);
        _cantidadFrutaText.setPosition(360.0f, 140.0f);  // Posici�n cant frutas
        _puntajesFrutasText.setString(puntosFrutas);
        _puntajesFrutasText.setPosition(530.0f, 140.0f);  // Posici�n puntaje frutas
    }
}

void Resultado::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(_resultadoSprite, states);
    //target.draw(tapaFondo, states);
    target.draw(_resultadoTituloSombra, states);
    target.draw(_resultadoTitulo, states);
    target.draw(_frutasText, states);
    target.draw(_cantidadFrutaText, states);
    target.draw(_puntajesFrutasText, states);
}
