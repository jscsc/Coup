#pragma once

namespace Util
{
	enum PlayerType { PLAYER_ONE, PLAYER_TWO };
	enum GameState { SETUP, GAMEPLAY };
	enum MovementType { FORWARD, BACK, LEFT_OR_RIGHT, DIAGONAL, SUPER, LEFT_OR_RIGHT_SUPER, DIAGONAL_SUPER, BACK_DIAGONAL_SUPER, BACK_DIAGONAL, STAY };
	enum AbilityType { MOVEMENT, MOD };

}