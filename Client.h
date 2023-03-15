#pragma once

#include <SFML/Network.hpp>
#include <iostream>

class Client
{
	private :
		std::string hostIP;
		int hostPort;

		sf::TcpSocket socket;

	public :
		
		Client();

		bool ConnectToHost();

		int ReceivePacket();

		bool SendPacket(int result);
};

