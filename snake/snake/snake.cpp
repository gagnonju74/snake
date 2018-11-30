
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, const char **argv) {

	// Declare and create a new render-window
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Zozor se promène", sf::Style::Close);
	sf::RectangleShape rectangle(sf::Vector2f(800, 600));
	rectangle.setFillColor(sf::Color::Black);

	sf::Texture textureFond;
	sf::Texture textureBonhomme;
	sf::Sprite sprite;

	if (!textureFond.loadFromFile("ressource/back-pattern.png"))
		return -1;

	rectangle.setTexture(&textureFond);

	if (!textureBonhomme.loadFromFile("ressource/charsets.bmp"))
		return -1;

	// Assign it to a sprite
	sprite.setTexture(textureBonhomme);

	int dir = 0,
		pos = 0,
		timer = 0;

	// Limit the framerate to 60 frames per second (this step is optional)
	window.setFramerateLimit(60);

	while (window.isOpen()) {                 // Is the window still opened?
		sf::Event event;                        // We create an event
		while (window.pollEvent(event)) {       // We fill the event from the window
			if (event.type == sf::Event::Closed)  // If the event is close window
				window.close();   // We close it ;)

			if (event.type == sf::Event::MouseMoved) {
				sprite.setPosition(event.mouseMove.x - (32 / 2), event.mouseMove.y - (32 / 2));
			}
			if (event.type == sf::Event::KeyReleased)
				switch (event.key.code) {
				case sf::Keyboard::Down:
					dir = 0;
					sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 10);
					break;
				case sf::Keyboard::Left:
					dir = 1;
					sprite.setPosition(sprite.getPosition().x - 10, sprite.getPosition().y);
					break;
				case sf::Keyboard::Right:
					dir = 2;
					sprite.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y);
					break;
				case sf::Keyboard::Up:
					dir = 3;
					sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10);
					break;
				default:
					break;
				}
		}

		window.clear(sf::Color::Blue);                         // This line clear the screen
		window.draw(rectangle);

		// Draw the textured sprite
		sprite.setTextureRect(sf::IntRect(32 * pos, 32 * dir, 32, 32));

		window.draw(sprite);
		window.display();                       // And we display the window

		++timer;
		if (!(timer % 6)) {						 // This is to slow the animation (update every 10ms [1/6 * 60FPS])
												 //------------------------------------------------------------------------//
			pos++;
			if (pos > 2)
				pos = 0;
		}
	}

	return 0;
}