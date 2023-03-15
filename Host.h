#pragma once

#include <SFML/Network.hpp>
#include <iostream>

class Host
{
	private: 
		sf::TcpListener listener;
		sf::TcpSocket client;

		std::string clientAdress, clientPort;

	public:

		bool BindListener();

		bool AcceptClient();

		sf::Packet ReceivePacket();

		bool SendPacket(sf::Packet packet);

};

