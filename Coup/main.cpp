#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <exception>
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
#include "Textures.h"

#include <random>
int main()
{
	// Create render window
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Coups");

	// TODO Swtich over to using Delta Time to help improve performance
	window.setFramerateLimit(500);

	// Create Textrues
	Textures textures;

	// Create player data
	PlayerData playerData(Util::PLAYER_ONE, textures);
	
	// Create AI data
	PlayerData AIData(Util::PLAYER_TWO, textures);
	
	// Create the game data
	GameData gameData;

	// Create font
	sf::Font gameFont;

	if (!gameFont.loadFromFile("Assets//Fonts//Roboto-Thin.ttf"))
	{
		throw "font failed to load";
	}

	// Create UI data
	UIData UI(textures, gameFont);

	// Create the player manager
	PlayerManager playerManager(playerData, AIData, gameData, UI, window);

	// Create the AI manager
	AIManager AI(AIData, gameData, UI);

	// Create the game manager
	GameManager gameManager(playerData, AIData, gameData, UI, window);

	// Create the renderer
	Renderer renderer(playerData, AIData, gameData, UI, window);

	// Start at menu, broken?
	gameData.currentGameState = Util::MAIN_MENU;

	/// GAME LOOP
	while (window.isOpen())
	{
		// Reset game items if needed
		if (gameData.mouseClicked == true)
			gameData.mouseClicked = false;


		// Hanndle Events
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
		window.clear(sf::Color::White);

		renderer.render();

		window.display();
	}

	return 0;
}