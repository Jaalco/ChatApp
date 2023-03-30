#include "server.h"
#include "accepter.h"
#include "queue.h"
#include "list.h"
#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

Server::Server()
{

}


int Server::run()
{
    Queue<std::string> queue_;
    List<std::shared_ptr<sf::TcpSocket>> sockets;
    // TODO launch an accepter thread.
//    std::shared_ptr<Accepter> accepter = std::make_shared<Accepter>(queue_, sockets);
    std::thread(Accepter(queue_, sockets));

    while(1)
    {
        std::string s = queue_.pop();
        std::cout << "Main read: \"" << s << "\"\n";
        // TODO send to all in sockets. Be careful to synchronise.

        auto send_to_one = [&s](std::shared_ptr<sf::TcpSocket> socket){
            sf::Socket::Status status = socket->send(s.c_str(), s.size() + 1);
            if(status != sf::Socket::Done)
            {
                std::cout << "Error sending\n";
                return;
            }
            return;
        };

        sockets.for_each(send_to_one);
    }
    return 0;
}
