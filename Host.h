#pragma once

#include <SFML/Network.hpp>
#include <iostream>

class Host
{
	private: 
		
		sf::TcpSocket client;

		std::string clientAdress, clientPort;

	public:
		sf::TcpListener listener;

		Host();

		bool BindListener();

		bool AcceptClient();

		int ReceivePacket();

		bool SendPacket(int result);

};

