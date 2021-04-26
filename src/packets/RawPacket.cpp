//
// Created by vince on 06.04.21.
//

#include "RawPacket.h"

RawPacket::RawPacket(unsigned char specificFlags,
                     unsigned char *data,
                     unsigned int length,
                     PacketType type) :
        _specificFlags(specificFlags),
        _data(data),
        _length(length),
        _type(type) {}

// should be autogenerated
//RawPacket::RawPacket(RawPacket const& p)
RawPacket::RawPacket(RawPacket *rawPacket)
        : _specificFlags(rawPacket->_specificFlags), _data(rawPacket->_data), _length(rawPacket->_length),
          _type(rawPacket->_type) {}

RawPacket::RawPacket() {}

RawPacket::~RawPacket() {
    delete _data;
}