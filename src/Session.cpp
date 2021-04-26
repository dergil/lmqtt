//
// Created by vince on 08.04.21.
//

#include "Session.h"
#include <list>




//std::list<RawPacket *> &PacketIOManager::modifyPacketsSent() {
//    return _packets_sent;
//}
//
//std::list<RawPacket *> &PacketIOManager::modifyPacketsReceived() {
//    return _packets_received;
//}


std::list<RawPacket *>* Session::getPacketsSent() {
    return _packets_sent;
}

std::list<RawPacket *>* Session::getPacketsReceived() {
    return _packets_received;
}

Session::Session(){
    _packets_received= new std::list<RawPacket*>();
    _packets_sent= new  std::list<RawPacket*>();
}

Session::~Session() {
    delete _packets_received;
    delete _packets_sent;
}