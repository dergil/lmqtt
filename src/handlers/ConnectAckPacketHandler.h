//
// Created by vince on 01.05.21.
//

#ifndef LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
#define LMQTT__SERVER_CONNECTACKPACKETHANDLER_H

#include <ConnectAckPacket.h>
#include <ClientConnectionSession.h>
#include "PacketHandler.h"

class ConnectAckPacketHandler : public PacketHandler<ConnectAckPacket,ClientConnectionSession>{
public:
    ConnectAckPacketHandler(ClientConnectionSession *connectionSession, PacketIOManager *packetIo);
    void handle(ConnectAckPacket *packet) override;
};


#endif //LMQTT__SERVER_CONNECTACKPACKETHANDLER_H
