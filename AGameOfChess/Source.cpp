#include<iostream>

#include <SFML/Graphics.hpp>

int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktop, "A Game of Chess", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	sf::View fullView(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
	fullView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	sf::Texture back;
	if (!back.loadFromFile("BackgroundFin.png"))
		std::cerr << "Unable to load background"<<std::endl;
	sf::Sprite background(back);


	window.setView(fullView);



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(background);
		window.display();
	}

	return 0;
}