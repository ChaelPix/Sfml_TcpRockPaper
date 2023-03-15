#pragma once
#include <SFML/Graphics.hpp>

sf::Texture GetTextureFromFile(std::string filename);

int SetChoosenElement(int id, sf::CircleShape& circle, sf::Vector2f elementPos);

char GetMode();

void Game();

int GetResult(int choice, int opponentChoice);