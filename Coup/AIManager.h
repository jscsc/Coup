#pragma once

//class Movement;
struct PlayerData;
struct GameData;
struct UIData;
class AIManager
{

	PlayerData &AIData;

	GameData &gameData;

	UIData &UI;

public:



	AIManager(PlayerData &AIData, GameData &gameData, UIData &UI);
	~AIManager();
	void AIPlayerLogic();
	void handelAIAbilitySetup();
	void handelAIPositionSetup();
	void handelAIGameplay();
	void determineMove();
	void tryMove();
	void handelBack();
	void handelStay();
	void handelLeftOrRight();
	void handelDiagonal();
	void handelSuper();
	void handelDefault();

	bool dangerForward();
	bool dangerForwardLeft();
	bool dangerForwardRight();
	bool dangerDiagonalLeft();
	bool dangerDiagonalRight();
	bool inDanger();
};

