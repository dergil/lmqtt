#ifndef __CONNACKPACKETPARSER_H__
#define __CONNACKPACKETPARSER_H__

#include "../RawPacket.h"
#include "PacketParser.h"
#include "../RawPacket.h"

class ConnectAckPacketParser : public PacketParser<ConnectAckPacket>{
public:
    ConnectAckPacket* parse(RawPacket* pRawPacket) override;
};

#endif // __CONNACKPACKETPARSER_H__