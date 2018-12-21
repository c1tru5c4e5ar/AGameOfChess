#include<iostream>
#include"Chess.h"
#include<SFML\Graphics.hpp>


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

	Piece P;
	P.assign('P', true, 1, 1);
	P.loadIcon();

	window.setView(fullView);

	ChessBoard b;
	b.printmainBoard();
	

/*
	sf::Texture t;
	if(!t.loadFromFile("pieces/WhitePawn.png"))
		std::cerr<<"NOT LOADING"<<std::endl;
	sf::Sprite box(t);
	sf::FloatRect dimentions = box.getLocalBounds();
	std::cout << dimentions.width;
	box.setOrigin((dimentions.width / 2), (dimentions.height / 2));
	box.setPosition(210.f, 190.f);
*/

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
		//window.draw(P.icon);
		b.displaymainBoard(window);
		//window.draw(box);
		window.display();
	}

	return 0;
}