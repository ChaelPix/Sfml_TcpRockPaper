#include <SFML/Graphics.hpp>
#include <iostream>

sf::Texture GetTextureFromFile(std::string filename)
{
    sf::Texture textureToLoad;
    std::string path = "Ressources/" + filename;
    textureToLoad.loadFromFile(path);

    return textureToLoad;
}

int SetChoosenElement(int id, sf::CircleShape &circle, sf::Vector2f elementPos)
{
    circle.setPosition(elementPos);


    return id;
}