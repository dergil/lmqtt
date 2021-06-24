


#include "ServerSession.h"


ServerSession::ServerSession(char *clientId) : _clientId(clientId){
    this->_subscriptions= new std::list<char *>;
}

std::ostream &operator<<(std::ostream &os, const ServerSession &session) {
    os << "_clientId: " << session._clientId << " _subscriptions: " << session._subscriptions;
    return os;
}

