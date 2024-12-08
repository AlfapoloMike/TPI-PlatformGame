#include "Menu.h"
#include <iostream>

/// CONSTRUCTOR
Menu::Menu() {

    selectedIndex = 0; // 
    currentState = intro; // Estado inicial
    nextState = menu;

    // CARGA FONT GENERAL
    if (!font.loadFromFile("./assets/fonts/Pixelon.ttf")) {
        std::cout << "Error al cargar la fuente" << std::endl;
    }

    //******************************* MENU *******************************
    // FONDO MENU
    if (!_fondoMenuTexture.loadFromFile("./assets/fondos/fondo.png")) {
        std::cout << "Error al cargar fondo menu" << std::endl;
    }
    _fondoMenuSprite.setTexture(_fondoMenuTexture); // Asignamos la textura al sprite

    // SONIDOS de navegacion ENTER - ERROR - TIPEO - BACKSPACE
    if (!_enter.openFromFile("./assets/audios/enter.mp3")) {
        std::cout << "Error al cargar la audio eleccion_menu" << std::endl;
    }
    if (!_error.openFromFile("./assets/audios/error.mp3")) {
        std::cout << "Error al cargar la audio _error" << std::endl;
    }
    if (!_letra.openFromFile("./assets/audios/tipeo.mp3")) {
        std::cout << "Error al cargar la audio _letras" << std::endl;
    }
    if (!_back.openFromFile("./assets/audios/backspace.mp3")) {
        std::cout << "Error al cargar la audio _backspace" << std::endl;
    }


    // FROGAR selector del menu
    if (!_selectorMenuTexture.loadFromFile("./assets/personaje/Frogar/Fall(32x32).png")) {
        std::cout << "Error al cargar imagen item selector" << std::endl;
    }
    _selectorMenuSprite.setTexture(_selectorMenuTexture);


    //******************************* ENTER NAME *******************************
    // FONDO ENTER NAME
    if (!_fondoNombreTexture.loadFromFile("./assets/fondos/fondo.png")) { // Ruta a la imagen de fondo
        std::cout << "Error al cargar fondo ingresoNombre" << std::endl;
    }
    _fondoNombreSprite.setTexture(_fondoNombreTexture); // Asignamos la textura al sprite

    //******************************* aux *******************************
    // TEXTOS PIE AUXILIARES
    pressText.setFont(font);
    pressText.setString("Presiona ESC para volver al menú");
    pressText.setCharacterSize(20);
    pressText.setOutlineThickness(4); // Grosor del contorno
    pressText.setScale(0.8f, 1.0f);
    pressText.setPosition(100.0f, 550.0f);

    nombrePress.setFont(font);
    nombrePress.setString("Escriba al menos una letra\nENTER para confirmar nombre  o  ESC para volver");
    nombrePress.setCharacterSize(20);
    nombrePress.setOutlineThickness(4); // Grosor del contorno
    nombrePress.setScale(0.8f, 1.0f);
    nombrePress.setPosition(100.0f, 550.0f);

}

Menu::~Menu() {
}


/////////////////////////////////////////// UPDATE ///////////////////////////////////////////
void Menu::update(sf::RenderWindow& window, bool& menuSi) {

    setMusica(); // Actualiza musica segun estado

    if (currentState == intro) {
        _intro.update(cambioEstado);
        if (cambioEstado) {
            currentState = nextState;
            cambioEstado = false;
            _musicaFondo.stop();
        }
    }

    if (cambioEstado) { // Chequeo cambio de estado;
        if (currentState == history && nextState == menu) {
            menuSi = false;
            _musicaFondo.stop();
        }

        if (_clockMenu.getElapsedTime().asSeconds() >= 0.4f) { // Seteo tiempo de transicion
            //if (currentState == history && nextState == menu) {
            //    menuSi = false;
            //}
            //if(currentState == result && nextState == menu){}
            _musicaFondo.stop();   // Stopeo la música de fondo
            currentState = nextState; // Actualizo el estado
            cambioEstado = false;  // Termina transicion   
        }
    }

    else if (currentState == menu) {

        /// CONFIGURACION OPCIONES MENU + SOMBRA
        // TITULO     
        menuTitulo.setFont(font);
        menuTitulo.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
        menuTitulo.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
        menuTitulo.setOutlineThickness(7); // Grosor del contorno
        menuTitulo.setString(menuTituloeText);
        menuTitulo.setCharacterSize(95);
        menuTitulo.setFillColor(sf::Color(180, 80, 80, 255));
        menuTitulo.setPosition(50.0f, -10.0f);
        menuTituloSombra.setFont(font);
        menuTituloSombra.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
        menuTituloSombra.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
        menuTituloSombra.setOutlineThickness(3.04f); // Grosor del contorno
        menuTituloSombra.setOutlineColor(sf::Color(20, 10, 10, 150)); // Color del contorno
        menuTituloSombra.setString(menuTituloeText);
        menuTituloSombra.setCharacterSize(95);
        menuTituloSombra.setFillColor(sf::Color(20, 10, 10, 250));
        menuTituloSombra.setPosition(60.0f, 30.0f);

        // OPCIONES
        float entrelineado = 60.0f; // Regula espacio entre opciones del menu. A partir de 38 para que no se pisen con Size(40)

        for (int i = 0; i < numOptions; ++i) {
            menuText[i].setFont(font); // Asigna la fuente a cada opción del menú
            menuText[i].setString(options[i]); // Asigna el texto de la opción
            menuText[i].setCharacterSize(40); // Establece el tamaño de la fuente
            menuText[i].setPosition(350.0f, 210.0f + i * entrelineado); // Establece la posición de cada opción
            menuText[i].setFillColor(sf::Color::White); // Establece el color del texto
            menuText[i].setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
            menuText[i].setOutlineThickness(5); // Grosor del contorno
            menuText[i].setOutlineColor(sf::Color::Black); // Color del contorno
            menuText[i].setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO

            // SOMBRA TEXTO
            sombra[i] = menuText[i];  // Copiar configuración de texto principal        
            sombra[i].setCharacterSize(40); // Tamaño texto sombra
            sombra[i].setOutlineThickness(3); // Grosor del contorno
            sombra[i].setOutlineColor(sf::Color(20, 10, 10, 200)); // Color del contorno
            sombra[i].setFillColor(sf::Color(20, 10, 10, 100));  // Color oscuro y un poco transparente
            sombra[i].move(10, 8);  // Desplazar ligeramente la sombra respecto de la posicion de opciones
        }
        _selectorMenuSprite.setPosition(310.0f, 217.0f + selectedIndex * entrelineado); // Posición del selector basado en la opción seleccionada


        /// OPCIONAL - Opcion en resaltada en tamaño y color
        /*
        menuText[selectedIndex].setFillColor(sf::Color(180, 80, 80, 255)); // Pongo en rojizo la opcion actual del menu.
        menuText[selectedIndex].setPosition(320.0f, 190.0f + selectedIndex * entrelineado);
        menuText[selectedIndex].setCharacterSize(70);
        sombra[selectedIndex].setFillColor(sf::Color(20, 10, 10, 220));
        sombra[selectedIndex].setPosition(320.0f, 190.0f + selectedIndex * entrelineado);
        sombra[selectedIndex].setCharacterSize(70);
        sombra[selectedIndex].move(10, 8);
        _selectorMenuSprite.setPosition(280.0f, 217.0f + selectedIndex * entrelineado); // Posición del selector basado en la opción seleccionada
        */
    }

    else if (currentState == enter_name) {

        // TEXTO INGRESO DE NOMBRE + Sombra
        nombreTitulo.setFont(font);
        nombreTitulo.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
        nombreTitulo.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
        nombreTitulo.setOutlineThickness(5); // Grosor del contorno
        nombreTitulo.setString("INGRESE SU NOMBRE");
        nombreTitulo.setCharacterSize(90);
        nombreTitulo.setFillColor(sf::Color(180, 80, 80, 255));
        nombreTitulo.setPosition(65.0f, 1.0f);
        nombreTituloSombra.setFont(font);
        nombreTituloSombra.setScale(0.8f, 1.0f); // 1.0 para mantener el ALTO, 0.8 para comprimir ANCHO
        nombreTituloSombra.setStyle(sf::Text::Bold); // Aplicar negrita para mayor espesor
        nombreTituloSombra.setOutlineThickness(3.f); // Grosor del contorno
        nombreTituloSombra.setOutlineColor(sf::Color(20, 10, 10, 150)); // Color del contorno
        nombreTituloSombra.setString("INGRESE SU NOMBRE");
        nombreTituloSombra.setCharacterSize(90);
        nombreTituloSombra.setFillColor(sf::Color(20, 10, 10, 250));
        nombreTituloSombra.setPosition(75.0f, 40.0f);

    }

    else if (currentState == statics) {
        _ranking.update(cambioEstado);
    }

    else if (currentState == credits) {
        _creditos.update();
    }

    else if (currentState == history) {
        _historia.update(_completa, _noComenzar);
    }

    else if (currentState == quit) {
        window.close();
    }

    else if (currentState == instructions) {
        _ayuda.update();
    }

    else if (currentState == result) {
        _resultado.update();
    }
}


/////////////////////////////////////////// DRAW ///////////////////////////////////////////
void Menu::draw(sf::RenderWindow& window) {

    //window.clear(); // Limpio ventana (podria estar en main antes de draw)

    if (currentState == intro) {
        window.draw(_intro);
    }

    else if (currentState == menu) {
        window.draw(_fondoMenuSprite); // Fondo
        for (int i = 0; i < numOptions; ++i) {
            window.draw(sombra[i]); // Sombra opcion
            window.draw(menuText[i]); // Cada opcion            
        }
        window.draw(menuTituloSombra); // Titulo sombra
        window.draw(menuTitulo); // Titulo
        window.draw(_selectorMenuSprite); // Frogar selector
    }

    else if (currentState == enter_name) {
        window.draw(_fondoNombreSprite); // Fondo
        window.draw(nombreTituloSombra); // Sombra titulo
        window.draw(nombreTitulo); // Titulo

        // NOMBRE QUE SE ESTA ESRIBIENDO
        sf::Text nombreParcial;
        nombreParcial.setFont(font);
        nombreParcial.setString(playerName); // El texto que se mostrara (el nombre ingresado)
        nombreParcial.setCharacterSize(60); // Tamaño letra a dibujar
        nombreParcial.setPosition(220.0f, 250.0f); // Posicion
        nombreParcial.setFillColor(sf::Color::White); // Color nombre BLANCO
        //nombreParcial.setFillColor(sf::Color(180, 80, 80, 255)); // Color nombre ROJIZO
        nombreParcial.setStyle(sf::Text::Bold); // Negrita
        nombreParcial.setOutlineThickness(5); // Grosor del contorno
        nombreParcial.setOutlineColor(sf::Color::Black); // Color contorno
        window.draw(nombreParcial); // Nombre parcial/final

        window.draw(nombrePress);
    }

    else if (currentState == statics) {
        window.draw(_ranking); // Ranking
        window.draw(pressText); // Aux
    }

    else if (currentState == credits) {
        window.draw(_creditos); // Creditos
        window.draw(pressText); // Aux
    }

    else if (currentState == history) {
        window.draw(_historia); // Historia
    }

    else if (currentState == instructions) {
        window.draw(_ayuda); // Como jugar
        window.draw(pressText); // Aux
    }

    else if (currentState == result) {
        window.draw(_resultado); // Como jugar
        //window.draw(pressText); // Aux
    }
    //window.display(); // Dibujos a pantalla (podria estar en main despues de draw)
}




/////////////////////////////////////////// MANEJO EVENTOS ///////////////////////////////////////////
void Menu::manejoEvents(sf::Event& event, bool& menuSi) {

    if (currentState == menu) {
        manejoInputs(event); // Manejo entrada en Menu
    }

    else if (currentState == enter_name) {
        manejoNameInput(event); // Manejo entrada teclado en "Ingreso de nombre"
    }

    else if (currentState == statics) {
        manejoInputs(event);  // Manejo entrada en Ranking
    }

    else if (currentState == credits) {
        manejoInputs(event); // Manejo entrada Creditos
    }

    else if (currentState == history) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                _enter.play();
                //_musicaFondo.stop();  comento por que stopeo en UPDATE
                nextState = menu;
                //nextState = result; // Para probar estado RESULT ***********************  ACA SETEO PARA IR A JUEGO

                //*********** Resetea texto de la historia para el proximo ingreso a historia
                _completa = true; // bandera true historia completa
                _noComenzar = false; // bandera vuelta historia desde el comienzo

                cambioEstado = true;
                _clockMenu.restart();
            }
            if (event.key.code == sf::Keyboard::Escape) {
                _musicaFondo.stop();
                currentState = enter_name; // Volver al menú de ingreso de nombre si se presiona Escape                

                //*********** Resetea texto de la historia
                _completa = true; // bandera true historia completa
                _noComenzar = false; // bandera vuelta historia desde el comienzo
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

                //*********** Autocompleta la historia
                _completa = true; // bandera historia completa
                _noComenzar = true; // bandera para que no comience la historia de nuevo
            }

        }

    }

    else if (currentState == instructions) {
        manejoInputs(event); // Manejo entrada Instrucciones
    }

    else if (currentState == result) {
        manejoInputs(event); // Manejo entrada Instrucciones
    }

}



/////////////////////////////////////////// MANEJO INPUTS ///////////////////////////////////////////
void Menu::manejoInputs(sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter
            && !cambioEstado
            && (currentState == menu || currentState == quit)) { // Para que ENTER solo actue en estos 2 estados.
            //_clockMenu.restart();
            if (_enter.getStatus() != sf::Music::Playing) {
                _enter.setVolume(100);
                _enter.play();
            }

            // Asignar el próximo estado según la opción seleccionada
            if (options[selectedIndex] == "JUGAR") {
                nextState = enter_name;
            }
            else if (options[selectedIndex] == "SALIR") {
                _enter.stop();
                nextState = quit;
            }
            else if (options[selectedIndex] == "RANKING") {
                nextState = statics;
            }
            else if (options[selectedIndex] == "CREDITOS") {
                nextState = credits;
            }
            else if (options[selectedIndex] == "COMO JUGAR") {
                nextState = instructions;
            }

            // Activar la transición y reiniciar el reloj
            cambioEstado = true;
            _clockMenu.restart();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            selectedIndex = (selectedIndex - 1 + numOptions) % numOptions; // Mover el selector hacia arriba
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            selectedIndex = (selectedIndex + 1) % numOptions; // Mover el selector hacia abajo
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (currentState == menu) {
                selectedIndex = numOptions - 1;
            }
            else {
                _musicaFondo.stop();
                currentState = menu;  // Volver al menú principal
            }

        }
    }
}



/////////////////////////////////////////// MANEJO ENTER_NAME ///////////////////////////////////////////
void Menu::manejoNameInput(sf::Event& event) {

    const int maxTamNombre = 12; // Tamaño máximo permitido para el nombre

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && playerName.length() > 0) { // Si se presiona Backspace(8)
            _back.play();
            playerName.pop_back(); // Eliminar el último carácter del nombre ingresado
        }
        else if (event.text.unicode <= 122 && playerName.length() < maxTamNombre) {
            char letratipeada = event.text.unicode; // Conversión a char
            // Validacion solo caracteres alfanumericos
            if ((letratipeada >= 'a' && letratipeada <= 'z') || // 97 - 122
                (letratipeada >= 'A' && letratipeada <= 'Z') || // 65 - 90
                (letratipeada >= '0' && letratipeada <= '9') || // 48 - 57
                letratipeada == ' ') { // 32
                playerName += letratipeada;
                _letra.play();
            }
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter && !cambioEstado) {
            _clockMenu.restart();
            if (!playerName.empty()) {
                if (_enter.getStatus() != sf::Music::Playing) {
                    _enter.setVolume(100);
                    _enter.play();
                }
                nextState = history;
                //_musicaFondo.stop();
                cambioEstado = true;
            }
            else {
                _error.play();
            }

            _clockMenu.restart();
        }
        else if (event.key.code == sf::Keyboard::Escape && !cambioEstado) {
            playerName = ""; // Limpiar el nombre si se cancela
            nextState = menu; // Volver al menú
            _musicaFondo.stop();
            cambioEstado = true;
        }

    }

}

void Menu::setMusica() {

    std::string rutaMusica;

    if (_musicaFondo.getStatus() != sf::Music::Playing) {
        switch (currentState) {
        case intro:
            rutaMusica = "./assets/audios/intro.wav";
            _musicaFondo.setVolume(100);
            break;
        case menu:
            rutaMusica = "./assets/audios/menu.mp3";
            _musicaFondo.setVolume(100);
            break;
        case enter_name:
            rutaMusica = "./assets/audios/enter_name.mp3";
            _musicaFondo.setVolume(100);
            break;
        case history:
            rutaMusica = "./assets/audios/historia.mp3";
            _musicaFondo.setVolume(100);
            //_musicaFondo.play();
            break;
        case instructions:
            rutaMusica = "./assets/audios/instrucciones.mp3";
            _musicaFondo.setVolume(40);
            //_musicaFondo.play();
            break;
        case statics:
            rutaMusica = "./assets/audios/ranking.mp3";
            _musicaFondo.setVolume(100);
            break;
        case credits:
            rutaMusica = "./assets/audios/creditos.mp3";
            _musicaFondo.setVolume(100);
            break;
        case result:
            rutaMusica = "./assets/audios/creditos.mp3";
            _musicaFondo.setVolume(0);
            break;
        }

        if (currentState != quit) {
            if (!_musicaFondo.openFromFile(rutaMusica)) {
                std::cout << "Error al cargar la musicaFondo: " << currentState << std::endl;
            }
            _musicaFondo.play();
        }
    }
}

void Menu::setState(std::string estado) {
    if (estado == "menu") {
        nextState = menu;
        cambioEstado = true;

    }
}

void Menu::setResultado(bool gano) {
    _resultado.setGano(gano);
    currentState = result;
}

void Menu::setFrutasRecolectadas(int frutas[]) {
    _resultado.setCantidadesRecolectadas(frutas);
}

std::string Menu::getNombreJugador() {
    return playerName;
}

int Menu::getPuntajeFinal() {
    return _resultado.getPuntajeTotal();
}

void Menu::resetAll() {
    selectedIndex = 0;
    //cambioEstado = false;
    //_completa = true;
    //_noComenzar = false;
    enterPress = false;
    playerName = "";
    _resultado.resetAll();
    //_historia.resetAll();
}
