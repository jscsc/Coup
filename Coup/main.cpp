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
	playerData.pieceMoving = false;
	LeftOrRight leftOrRight;
	Diagonal diagonal;
	Back back;
	playerData.movements.push_back(&leftOrRight);
	playerData.movements.push_back(&diagonal);
	playerData.movements.push_back(&back);
	

	GameData gameData;
	gameData.currentGameState = Util::GAMEPLAY;
	gameData.currentTurn = Util::PLAYER_ONE;
	gameData.mouseClicked = false;

	// Create game pieces
	GamePiece pieceOne(Util::PLAYER_TWO, 300, 600, 4, 0, 10.0f);
	GamePiece pieceTwo(Util::PLAYER_TWO, 500, 600, 4, 2, 10.0f);

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

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				gameData.mouseClicked = true;
			}
		}

		/// GAME LOGIC
		gameManager.playerLogic();

		gameManager.gameLogic();

		/// DRAW
		window.clear();

		gameManager.render();


		/*PlayerData testData;

		LeftOrRight test;
		Diagonal testTwo;

		testData.movements.push_back(new LeftOrRight());

		window.draw(testData.movements[0]->rect);*/

		window.display();
	}

	return 0;
}