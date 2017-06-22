#pragma once
#include <SFML/Graphics.hpp>

struct PlayerData;
struct GameData;
struct UIData;
class Renderer
{

	PlayerData &playerData;

	PlayerData &otherPlayerData;

	GameData &gameData;

	UIData &UI;

	sf::RenderWindow &window;

public:

	Renderer(PlayerData &playerData, PlayerData &otherPlayerData, GameData &gameData, UIData &UI, sf::RenderWindow &window);
	~Renderer();

	void render();
	void renderAbilitySetup();
	void renderPositionSetup();
	void renderGameplay();
};

