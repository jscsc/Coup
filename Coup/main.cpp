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
#include "PlayerManager.h"
#include "AIManager.h"
#include "GameManager.h"
#include "UIData.h"
#include "Renderer.h"

#include <random>
int main()
{
	/// INITIAL VARIABLES
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Coup");

	// Create player data
	PlayerData playerData(Util::PLAYER_ONE);
	
	// Create AI data
	PlayerData AIData(Util::PLAYER_TWO);

	//for (GamePiece* piece : AIData.pieces)
		//if (piece->isActive())
			//std::cout << "This is good?" << std::endl;
	
	// Create the game data
	GameData gameData;

	// Create UI data
	UIData UI;

	// Create the player manager
	PlayerManager playerManager(playerData, AIData, gameData, UI, window);

	// Create the AI manager
	AIManager AI(AIData, gameData, UI);

	// Create the game manager
	GameManager gameManager(playerData, AIData, gameData, UI, window);

	// Create the renderer
	Renderer renderer(playerData, AIData, gameData, UI, window);


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
		playerManager.playerLogic();

		AI.AIPlayerLogic();

		gameManager.gameLogic();

		/// DRAW
		window.clear();

		renderer.render();

		window.display();
	}

	return 0;
}