#pragma once

struct PlayerData;
struct GameData;
struct UIData;

// Manager the AI Player in the game
class AIManager
{

	// Reference to the data for the AI player
	PlayerData &AIData;

	// REference to the data for the overall game
	GameData &gameData;

	// Reference to the data for the UI
	UIData &UI;

public:

	// Constructor / Destructor
	AIManager(PlayerData &AIData, GameData &gameData, UIData &UI);
	~AIManager();

	// Starts the flow of the AI Player logic
	void AIPlayerLogic();

	// Begins to handel the behavior of the AI in the Ability Setup state
	void handleAIAbilitySetup();

	// // Begins to handel the behavior of the AI in the Position Setup state
	void handleAIPositionSetup();

	// Begins to handel the behavior of the AI in the Gameplay state
	void handleAIGameplay();

	// Determines which move the AI should make
	void determineMove();

	// Tries to move the AI, if it can
	void tryMove();

	// Handlers for each type of movement
	void handleBack();
	void handleStay();
	void handleLeftOrRight();
	void handleDiagonal();
	void handleSuper();
	void handleDefault();

	// Fuctions to determine if a move is dangerous for the AI
	bool dangerForward();
	bool dangerForwardLeft();
	bool dangerForwardRight();
	bool dangerDiagonalLeft();
	bool dangerDiagonalRight();

	// Determines if the AI is in danger
	bool inDanger();
};

