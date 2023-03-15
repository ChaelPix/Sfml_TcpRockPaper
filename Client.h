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

		bool ConnectToHost();
};

