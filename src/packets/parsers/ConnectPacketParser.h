//
// Created by vince on 06.04.21.
//

#ifndef LMQTT__SERVER_CONNECTPACKETPARSER_H
#define LMQTT__SERVER_CONNECTPACKETPARSER_H

#include "../ConnectPacket.h"
#include "../RawPacket.h"
#include "PacketParser.h"
#include "../RawPacket.h"

class ConnectPacketParser : public PacketParser/*<ConnectPacket>*/{
public:
//    ConnectPacket* parse(RawPacket* pRawPacket);
    RawPacket* parse(RawPacket* pRawPacket);
};


#endif //LMQTT__SERVER_CONNECTPACKETPARSER_H
