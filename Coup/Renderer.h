#pragma once
#include <SFML/Graphics.hpp>

struct PlayerData;
struct GameData;
struct UIData;

// Class to handle rendering items to the screen and in which order they render
class Renderer
{

	// Reference to player data
	PlayerData &playerData;

	// Reference to the other player data
	PlayerData &otherPlayerData;

	// Reference to overall game data
	GameData &gameData;

	// Reference to UI data
	UIData &UI;

	// Reference to the window to draw to
	sf::RenderWindow &window;

public:

	// Constructor / Destructor
	Renderer(PlayerData &playerData, PlayerData &otherPlayerData, GameData &gameData, UIData &UI, sf::RenderWindow &window);
	~Renderer();

	// Functions to control rendering based on game state, with the root of the logic starting in render()
	void render();
	void renderMainMenu();
	void renderAbilitySetup();
	void renderPositionSetup();
	void renderGameplay();
	void renderGameOver();
};

