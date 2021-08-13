//
// Created by vince on 11.08.21.
//

#include <SubscribePacket.h>
#include <InvalidPacketException.h>
#include <SubAckPacket.h>
#include "SubscribePacketHandler.h"

SubscribePacketHandler::SubscribePacketHandler(PacketIOManager *packetIo,
                                               ServerSessionRepository *serverSessionRepository,
                                               ServerConnection *serverConnection,
                                               SubAckPacketFactory *subAckPacketFactory,
                                               TopicRepository *topicRepository)
        : PacketHandler(packetIo), _serverSessionRepository(serverSessionRepository),
          _serverConnection(serverConnection), _subAckPacketFactory(subAckPacketFactory),
          topicRepository(topicRepository) {}
void SubscribePacketHandler::handle(RawPacket *packet) {
    SubscribePacket* subscribePacket = static_cast<SubscribePacket*>(packet);
    if (subscribePacket->getQos() > 3 || subscribePacket->getQos() < 0){
        //todo return ret code 0x80 to indicate error instead of exception
        throw InvalidPacketException("qos must be 0 - 3 ");
    }

    if (strlen(subscribePacket->getTopic())<=1){
        throw InvalidPacketException("topic len must be > 1");
    }

    ServerSession* serverSession = _serverConnection->_serverSession;

    char *qos_topic = (char *) malloc(strlen((char*) subscribePacket->getQos()) + strlen(subscribePacket->getTopic()) + 1);
    strcat(qos_topic,(char*) subscribePacket->getQos());
    strcat(qos_topic,subscribePacket->getTopic());
    serverSession->_qos_subscriptions->push_back(qos_topic);
    _serverSessionRepository->save(serverSession);
    Topic* storedTopic = topicRepository->findTopic(subscribePacket->getTopic());
    if (storedTopic == 0){
        // send err ret code and quit connection
        SubAckPacket* errPacket = _subAckPacketFactory->create(subscribePacket->getPacketId(),0x80);
        _packetIo->sendPacket(errPacket);
        throw InvalidPacketException("Topic does not exist");
    } else{
        storedTopic->_subscribed_user_count += 1;
        SubAckPacket* successPacket = _subAckPacketFactory->create(subscribePacket->getPacketId(), (unsigned char) subscribePacket->getQos());
        _packetIo->sendPacket(successPacket);
        // todo send publish msg'es to let client consume all msges of topic
    }

}
