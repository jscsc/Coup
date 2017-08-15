#pragma once
#include <SFML/Graphics.hpp>
#include "BoardObject.h"
#include "Util.h"

// Class representing a node on the game board
class BoardNode : public BoardObject
{

	// Whether or not this BoardNode can be moved to
	bool valid = false;

	// The current player (if any) assingned to this BoardNode
	Util::PlayerType assignment = Util::NEUTRAL;

public:
	
	// SFML Circle for the body of this node
	sf::CircleShape body;

	// Constructors / Destructors
	BoardNode();
	BoardNode(float x, float y, int row, int column, float size);
	~BoardNode();

	// Getters and Setters
	void setValid(bool valid);
	bool isValid();
	Util::PlayerType getAssignment();
	void setAissignment(Util::PlayerType assignment);

	// Renders this BoardNode to the given window
	void render(sf::RenderWindow &window) override;
};

