#ifndef ACCEPTER_HPP
#define ACCEPTER_HPP

#include "queue.h"
#include "list.h"
//#include <


#include <SFML/Network.hpp>

class Accepter {
    private:
        Queue<std::string>& queue_;
        List<std::shared_ptr<sf::TcpSocket>>& socket_;

    public:
        Accepter(Queue<std::string>& q, List<std::shared_ptr<sf::TcpSocket>>& s);
        void operator()();
};


#endif
