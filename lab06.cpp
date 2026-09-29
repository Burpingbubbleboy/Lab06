#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int main() {

	sf::Clock clock = sf::Clock();
	sf::Int64 timeToCloseWindow = sf::Int64(2000000); // ~2 seconds
	sf::Int64 currentTime = sf::Int64(0);

	string background = "images1/backgrounds/winter.png";
	string foreground = "images1/characters/yoda.png";
	
	Texture backgroundTex;
	if (!backgroundTex.loadFromFile(background)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}

	Texture foregroundTex;
	if (!foregroundTex.loadFromFile(foreground)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}

	Image backgroundImage;
	backgroundImage = backgroundTex.copyToImage();

	Image foregroundImage;
	foregroundImage = foregroundTex.copyToImage();

	Vector2u BGImageSize = backgroundImage.getSize();
	
	for (int y = 0; y < BGImageSize.y; y++) {
		for (int x = 0; x < BGImageSize.x; x++) {
			
			Color backgroundPixel = backgroundImage.getPixel(x, y);
			Color foregroundPixel = foregroundImage.getPixel(x, y);
			
			// this is doing weird less than and greater than checks because I don't actually know the actual color values of each pixel
			// this was found through pure guesswork and uses super magical magic numbers.
			if (foregroundPixel.r < 128 && foregroundPixel.g > 210 && foregroundPixel.b < 128) {
				foregroundImage.setPixel(x, y, backgroundPixel);
			}
		}
	}
	
	RenderWindow window(VideoMode(1024, 768), "MMO JRPG METROIDVANIA");
	Sprite sprite1;
	Texture tex1;
	
	// we actually just wrote to the foreground image instead of creating a new one, so use that.
	tex1.loadFromImage(foregroundImage);
	sprite1.setTexture(tex1);
	window.clear();
	window.draw(sprite1);
	window.display();
	
	while (currentTime < timeToCloseWindow) {
		sf::Int64 deltaTime = clock.getElapsedTime().asMicroseconds();
		
		currentTime += deltaTime;
	
		clock.restart();
	}
}