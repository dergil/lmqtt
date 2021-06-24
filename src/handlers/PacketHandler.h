//
// Created by vince on 01.04.21.
//

#ifndef LMQTT__SERVER_PACKETHANDLER_H
#define LMQTT__SERVER_PACKETHANDLER_H

#include "../packets/RawPacket.h"
#include "../con/ConnectionSession.h"
#include "../io/PacketIOManager.h"


// S = type of session, P = type of Packet
template<class P, class S>
class PacketHandler {
public:
    PacketHandler(S *connectionSession, PacketIOManager *packetIo);
    virtual void handle(P *packet) = 0;

protected:
    S *_connectionSession;
    PacketIOManager *_packetIo;
};

template<class P, class S>
PacketHandler<P, S>::PacketHandler(S *connectionSession, PacketIOManager *packetIo):_connectionSession(
        connectionSession), _packetIo(packetIo) {}

#endif //LMQTT__SERVER_PACKETHANDLER_H
