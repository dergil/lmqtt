//
// Created by vince on 10.09.21.
//

#ifndef LMQTT__SERVER_PUBLISHCLIMODEHANDLER_H
#define LMQTT__SERVER_PUBLISHCLIMODEHANDLER_H


#include <PublishPacketFactory.h>
#include "CLIModeHandler.h"

class PublishCLIModeHandler : public CLIModeHandler{
    ClientsClientInfoRepository *clientSessionRepository;
    PublishPacketFactory *publishPacketFactory;

public:
    PublishCLIModeHandler(char **argv, ClientConnectionManager *clientConnectionManager,
                          ConnectPacketFactory *connectPacketFactory, int argc,
                          ClientsClientInfoRepository *clientSessionRepository, PublishPacketFactory *publishPacketFactory);

    void handle() override;



};


#endif //LMQTT__SERVER_PUBLISHCLIMODEHANDLER_H
