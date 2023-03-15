#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>

#include "Functions.h"
#include "Host.h"
#include "Client.h"

Host host;
Client client;
bool isHost = false;
int result;

int main()
{
    char mode = GetMode();

    if (mode == 'h')
    {
        isHost = true;

        //bind port
        if (!host.BindListener())
        {
            std::cout << "Binding Port error...";
            return -1;
        } std::cout << "Port binded!" << std::endl;


        //connect to client
        if (!host.AcceptClient())
        {
            std::cout << "Synchro error...";
            return -2;
        } std::cout << "Client Found!" << std::endl;

    }
    else client.ConnectToHost();

    Game();

    return 0;
}


void Game()
{
    sf::Vector2f windowSize(1280, 720);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "TCP : Pierre Feuille Ciseaux !");
   
    //Icon
    sf::Image icon;
    icon.loadFromFile("Ressources/Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    //Textures
    sf::Texture paperTexture = GetTextureFromFile("paper.png");
    sf::Texture stoneTexture = GetTextureFromFile("stone.png");
    sf::Texture scissorsTexture = GetTextureFromFile("scissors.png");

    //Sprites
        //paper
    sf::RectangleShape paper(sf::Vector2f(120, 120));
    paper.setTexture(&paperTexture);
    paper.setOrigin(60, 60);
    paper.setPosition(windowSize.x / 2, windowSize.y / 2 + 120);
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
    opponentChoice.setPosition(325, windowSize.y - 65);

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
    opponentChoiceTxt.setString("");
    opponentChoiceTxt.setOrigin(0, 0);
    opponentChoiceTxt.setPosition(25, windowSize.y - 50);

    //Won/loose
    sf::Text resultText = opponentChoiceTxt;
    resultText.setCharacterSize(50);
    resultText.setString("");
    resultText.setOrigin(0, 0);
    resultText.setPosition(850, windowSize.y - 100);

    //Restart
    sf::Text restartText = opponentChoiceTxt;
    restartText.setCharacterSize(25);
    restartText.setString("Press R to restart");
    restartText.setOrigin(resultText.getGlobalBounds().width / 2, resultText.getGlobalBounds().height / 2);
    restartText.setPosition(windowSize.x/2 - 100, 100);


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

        //Restart
        if (hasChoosenElement && hasOpponentChoosen && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            hasChoosenElement = false;
            hasOpponentChoosen = false;
            opponentChoiceTxt.setString("");
            resultText.setString("");
        }

        //Wait opponent
        if (hasChoosenElement && !hasOpponentChoosen)
            opponentChoiceTxt.setString("Waiting Opponent..."); 
        
        //Draw
        if (hasChoosenElement) window.draw(choiceCircle);
        window.draw(opponentChoiceTxt);

        if (hasChoosenElement && hasOpponentChoosen)
        {
            window.draw(restartText);
            window.draw(opponentChoice);
        }
       
        window.draw(resultText);
        window.draw(paper);
        window.draw(stone);
        window.draw(scissors);

        window.draw(pickObjectTxt);

        window.display();

        //Check Result
        if (hasChoosenElement && !hasOpponentChoosen)
        {
            hasOpponentChoosen = true;
            int opponentChoiceId;

            //Get Other player Choice and compare results
            if (isHost) //Can be optimized.....
            {
                host.SendPacket(elementChoosenId);
                opponentChoiceId = host.ReceivePacket();

                result = GetResult(elementChoosenId, opponentChoiceId);
            }
            else {
                client.SendPacket(elementChoosenId);
                opponentChoiceId = client.ReceivePacket();

                result = GetResult(elementChoosenId, opponentChoiceId);
            }

            //Write if you won
            switch (result)
            {
                case -1: resultText.setString("You lost..."); break;
                case 0: resultText.setString("Draw..."); break;
                case 1: resultText.setString("You won !"); break;
            }

            //show opponent choice in sprite
            opponentChoiceTxt.setString("Opponent choice : ");
            switch (opponentChoiceId)
            {
                case 0: opponentChoice.setTexture(&paperTexture, true); break;
                case 1: opponentChoice.setTexture(&stoneTexture, true); break;
                case 2: opponentChoice.setTexture(&scissorsTexture, true); break;
            }
        }
    }
}