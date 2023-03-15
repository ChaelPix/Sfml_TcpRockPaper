#include <SFML/Graphics.hpp>
#include <iostream>

sf::Texture GetTextureFromFile(std::string filename)
{
	sf::Texture textureToLoad;
	std::string path = "Ressources/" + filename;
	textureToLoad.loadFromFile(path);

	return textureToLoad;
}

int SetChoosenElement(int id, sf::CircleShape& circle, sf::Vector2f elementPos)
{
	circle.setPosition(elementPos);
	return id;
}

char GetMode()
{
	char mode;

	bool isCorrectInput = false;

	while (!isCorrectInput)
	{
		system("cls");
		std::cout << "Do you want to be the Host or join a server ? "
			<< std::endl << "[H] Host"
			<< std::endl << "[J] Join"
			<< std::endl;

		std::cin >> mode;

		switch (mode)
		{
			case 'h':
			case 'H': mode = 'h'; isCorrectInput = true; break;
			case 'j':
			case 'J': mode = 'j'; isCorrectInput = true;
		}
	}

	return mode;

}

int GetResult(int choice, int opponentChoice)
{
	int result = -1; //lose
	if (choice == opponentChoice)
		result = 0; //draw
	else if ((choice + 1) % 3 == opponentChoice)
		result = 1; //win

	return result;
}