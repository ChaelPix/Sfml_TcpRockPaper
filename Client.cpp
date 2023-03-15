#include "Client.h"

Client::Client()
{
	socket.setBlocking(true);
}

bool Client::ConnectToHost()
{
    bool isSucess = false;
    
    while (!isSucess)
    {
        std::cout << "Write Host @ IP : ";
        std::cin >> hostIP;
        std::cout << "Write Host Port (4444) : ";
        std::cin >> hostPort;

        if (socket.connect(sf::IpAddress(hostIP), hostPort, sf::seconds(2)) != sf::Socket::Done)
        {
            std::cout << "Error. Do you want do retry? (y/n) " << std::flush;
            char r; std::cin >> r;
            if (r == 'n') return false;
        }
        else isSucess = true;

    }
       
    return isSucess;

}

int Client::ReceivePacket()
{
    sf::Packet packet;
    int result;

    if (socket.receive(packet) != sf::Socket::Done)
    {
        std::cout << "Erreur recu de message" << std::endl;
        return -1;
    }

    packet >> result;

    return result;
}

bool Client::SendPacket(int result)
{
    sf::Packet packet;
    packet << result;

    bool isSucess = socket.send(packet) != sf::Socket::Done;
    return isSucess;
}
