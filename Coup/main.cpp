#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "main.h"
#include "Movement.h"
#include "BoardNode.h"
#include "GamePiece.h"
#include "Arrive.h"
#include "Kinematic.h"
#include "SteeringOutput.h"
#include "Back.h"
#include "LeftOrRight.h"
#include "Diagonal.h"
#include "PlayerData.h"
#include "GameData.h"
#include "GameManager.h"
int main()
{
	/// INITIAL VARIABLES
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Coup");

	// Create player manager
	PlayerData playerData;

	playerData.type = Util::PLAYER_ONE;
	playerData.points = 4;
	playerData.movements.push_back(&LeftOrRight());
	playerData.movements.push_back(&Diagonal());
	playerData.movements.push_back(&Back());
	

	GameData gameData;
	gameData.currentGameState = Util::GAMEPLAY;
	gameData.currentTurn = Util::PLAYER_ONE;
	gameData.mouseClicked = false;

	// Create game pieces
	GamePiece pieceOne(Util::PLAYER_TWO, 300, 600, 4, 0, 10.0f);
	GamePiece pieceTwo(Util::PLAYER_TWO, 300, 600, 4, 2, 10.0f);

	playerData.pieces.push_back(pieceOne);
	playerData.pieces.push_back(pieceTwo);

	// Create the game manager
	GameManager  gameManager(playerData, gameData, window);


	/// GAME LOOP
	while (window.isOpen())
	{

		// Reset stuff
		if (gameData.mouseClicked == true)
			gameData.mouseClicked = false;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
				gameData.mouseClicked = true;
		}

		/// GAME LOGIC
		//gameManager.playerLogic();

		//gameManager.gameLogic();

		/// DRAW
		window.clear();

		//gameManager.render();

		sf::RectangleShape rect(sf::Vector2f(100, 100));
		rect.setPosition(sf::Vector2f(300, 700));
		rect.setFillColor(sf::Color::Green);
		//window.draw(rect);

		//LeftOrRight *testPointer;

		//LeftOrRight test;

		//testPointer = &test;

		//window.draw(testPointer->rect);

		//std::cout << playerData.movements[0]->getCost() << std::endl;
		//window.draw(playerData.movements[0]->rect);

		window.display();
	}

	return 0;
}