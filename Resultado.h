#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Resultado : public sf::Drawable {
public:
	Resultado();
	~Resultado();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setGano(bool vencio);
	void setCantidadesRecolectadas(int frutas[]);
	int getPuntajeTotal();
	void resetAll();

private:
	sf::Font font;
	sf::Music conteoPuntos;
	sf::Music gameover;
	bool gameoverPlayed = false;

	sf::Texture _resultadoTexture;
	sf::Sprite _resultadoSprite;
	std::string _rutaImagen;
	sf::RectangleShape tapaFondo;
	sf::Sprite tapaFondoSprite;

	std::string resultado;
	bool gano = false;
	float counter = 245.0f;


	sf::Text _resultadoTitulo;
	sf::Text _resultadoTituloSombra;

	sf::Text _frutasText;
	sf::Text _cantidadFrutaText;
	sf::Text _puntajesFrutasText;

	sf::Text pressTextResultado;

	// Vectores     Manzana, Banana, Frutilla, Kiwi, Naranja, Cereza, Anana, Melon

	int contadores[8]{};
	
	int cantidades[8]{};

	int puntosFruta[8]{};
	bool contada[8]{ false };
	std::string espacioCant[8]{};
	std::string espacioPuntos[8]{};
	std::string espacioTotales[2]{};

	/// TOTALES
	int cantidadTotal = 0;
	int puntosTotal = 0;


	std::string frutas;
	std::string cantFrutas;
	std::string puntosFrutas;
};


