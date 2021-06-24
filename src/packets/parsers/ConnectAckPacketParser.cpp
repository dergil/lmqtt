
#include "../ConnectAckPacket.h"
#include "../RawPacket.h"
#include "PacketParser.h"
#include "../RawPacket.h"
#include "ConnectAckPacketParser.h"

ConnectAckPacket* ConnectAckPacketParser::parse(RawPacket* packet)
{
    unsigned char* data = packet->getData();
    unsigned char sessionPresent = data[0];
    unsigned char retCode = data[1];
    return new ConnectAckPacket(packet,sessionPresent,retCode);
}
