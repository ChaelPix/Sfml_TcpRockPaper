#include <SFML/Graphics.hpp>

#include <iostream>
#include "Functions.h"

int main()
{
    sf::Vector2f windowSize(1280, 720);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "TCP : Pierre Feuille Ciseaux !");

    //Textures
    sf::Texture paperTexture = GetTextureFromFile("paper.png");
    sf::Texture stoneTexture = GetTextureFromFile("stone.png");
    sf::Texture scissorsTexture = GetTextureFromFile("scissors.png");

    //Sprites
        //paper
    sf::RectangleShape paper(sf::Vector2f(120, 120));
    paper.setTexture(&paperTexture);
    paper.setOrigin(60, 60);
    paper.setPosition(windowSize.x/2, windowSize.y/2 + 120);

        //rock
    sf::RectangleShape stone(sf::Vector2f(120, 120));
    stone.setTexture(&stoneTexture);
    stone.setOrigin(60, 60);
    stone.setPosition(windowSize.x / 2 - 240, windowSize.y / 2 + 120);

        //scissors
    sf::RectangleShape scissors(sf::Vector2f(120, 120));
    scissors.setTexture(&scissorsTexture);
    scissors.setOrigin(60, 60);
    scissors.setPosition(windowSize.x / 2 + 240, windowSize.y / 2 + 120);

        //green circle
    sf::CircleShape choiceCircle(80);
    choiceCircle.setFillColor(sf::Color::Green);
    choiceCircle.setOrigin(choiceCircle.getGlobalBounds().width / 2, choiceCircle.getGlobalBounds().height / 2);

        //Ennemy choice
    sf::RectangleShape opponentChoice(sf::Vector2f(120, 120));
    opponentChoice.setOrigin(60, 60);
    opponentChoice.setPosition(550, windowSize.y - 50);

    //Font
    sf::Font font;
    font.loadFromFile("Ressources/hl.ttf");

    //Texts
        //choose object
    sf::Text pickObjectTxt;
    pickObjectTxt.setFont(font);
    pickObjectTxt.setCharacterSize(35);
    pickObjectTxt.setString("Choose Paper, Rock or Scissors");
    pickObjectTxt.setFillColor(sf::Color::Black);
    pickObjectTxt.setOrigin(pickObjectTxt.getGlobalBounds().width / 2, pickObjectTxt.getGlobalBounds().height / 2);
    pickObjectTxt.setPosition(windowSize.x / 2, windowSize.y / 2 - 120);

        //Ennemy choice
    sf::Text opponentChoiceTxt = pickObjectTxt;
    opponentChoiceTxt.setCharacterSize(15);
    opponentChoiceTxt.setString("Your opponent has choosen : ");
    opponentChoiceTxt.setOrigin(0, 0);
    opponentChoiceTxt.setPosition(25, windowSize.y - 50);

        //Won/loose
    sf::Text resultText = opponentChoiceTxt;
    resultText.setCharacterSize(25);
    resultText.setString("");
    resultText.setOrigin(0, 0);
    resultText.setPosition(850, windowSize.y - 35);

    //Game Variables
    bool hasChoosenElement = false;
    sf::Vector2f mousePosition;
    bool isClickReleased = true;
    int elementChoosenId;

    bool hasOpponentChoosen = false;

    while (window.isOpen())
    {
        sf::Event evenement;
        while (window.pollEvent(evenement))
        {
            if (evenement.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

        //Choose
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        {
            if (isClickReleased)
            {
                if (!hasChoosenElement)
                {
                    isClickReleased = false;
                    if (paper.getGlobalBounds().contains(mousePosition)) elementChoosenId = SetChoosenElement(0, choiceCircle, paper.getPosition());
                    else if (stone.getGlobalBounds().contains(mousePosition)) elementChoosenId = SetChoosenElement(1, choiceCircle, stone.getPosition());
                    else if (scissors.getGlobalBounds().contains(mousePosition)) elementChoosenId = SetChoosenElement(2, choiceCircle, scissors.getPosition());
                    else elementChoosenId = -1;

                    if (elementChoosenId >= 0) hasChoosenElement = true;
                }
            }
        }
        else isClickReleased = true;

        if (hasChoosenElement) window.draw(choiceCircle);
        if (hasOpponentChoosen) window.draw(opponentChoiceTxt);

        window.draw(opponentChoice);
        window.draw(resultText);
        window.draw(paper);
        window.draw(stone);
        window.draw(scissors);

        window.draw(pickObjectTxt);

        window.display();
    }

    return 0;
}