#include "Host.h"

Host::Host()
{
    client.setBlocking(true);
}


bool Host::BindListener()
{
    bool isSucess = listener.listen(4444) == sf::Socket::Done;
    return isSucess;
}

bool Host::AcceptClient()
{
    bool isSucess = listener.accept(client) == sf::Socket::Done;
    
    std::cout << "l'utilisateur a rejoint !" << std::endl
        << "Ip : " << client.getRemoteAddress() << std::endl
        << "Port : " << client.getRemotePort() << std::endl << std::endl;
    
    return isSucess;
}

int Host::ReceivePacket()
{
    sf::Packet packet;
    int result;

    if (client.receive(packet) != sf::Socket::Done)
    {
        std::cout << "Erreur recu de message" << std::endl;
        return -1;
    }

    packet >> result;

    return result;
}

bool Host::SendPacket(int result)
{
    sf::Packet packet;
    packet << result;

    bool isSucess = client.send(packet) == sf::Socket::Done;
    return isSucess;
}