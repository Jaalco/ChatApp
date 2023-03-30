#include "queue.h"
#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

int mainclient()
{
    std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
//    auto connect = [&] { return socket->connect(sf::IpAddress::getLocalAddress(), PORT); };
//    net_run(connect, "connect");
// TODO ask the user for address
    sf::Socket::Status status = socket->connect(sf::IpAddress::getLocalAddress(), PORT);
    if (status != sf::Socket::Done) {
        return 1;
    }
    std::cout << "Connected\n";
    Queue<std::string> queue_;
    // TODO launch a receiver thread to receive messages from the server.
    std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>(socket, queue_);
    std::thread(&Receiver::recv_loop, receiver).detach();
    std::string s = "";
    while (1)
    {
        std::getline(std::cin, s);
        std::cout << "Sending: \"" << s << "\"" << std::endl;
        // TODO send messages to the server
        status = socket->send(s.c_str(), s.size() + 1);
        if(status != sf::Socket::Done)
        {
            std::cout << "Error sending\n";
            return 1;
        }
    }
    return 0;
}
