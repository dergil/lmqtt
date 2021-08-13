#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <DisconnectPacketParser.h>
#include <SubscribePacketParser.h>
#include <SubAckPacketFactory.h>

#include "io/PacketIOManager.h"
#include "packets/ConnectPacket.h"
#include "packets/parsers/PacketParser.h"
#include "packets/parsers/ConnectPacketParser.h"
#include "handlers/ConnectPacketHandler.h"
#include "handlers/PacketHandler.h"
#include "con/ServerConnection.h"
#include "util/Utils.h"
#include "files/FileDataManager.h"
#include "ConnectionManager.h"


#define PORT 8080

static void createSessionDirectories(){
    const char* targetDir = "/.lmqtt/server/sessions";
    char* home = getenv("HOME");
    char* dir = (char*) malloc(strlen(home) + strlen(targetDir) + 1);
    strcpy(dir, home);
    strcat(dir,"/.lmqtt");
    Utils::createDirectory(dir);
    strcat(dir,"/server");
    Utils::createDirectory(dir);
    strcat(dir,"/sessions");
    Utils::createDirectory(dir);
}



int main(int argc, char const *argv[])
{
    createSessionDirectories();
    // THESE OBJECTS LIVE AS LONG AS THE SERVER
    // PARSERS
    std::map<PacketType,PacketParser*> parsers;
    ConnectPacketParser* connectPacketParser = new ConnectPacketParser;
    DisconnectPacketParser* disconnectPacketParser = new DisconnectPacketParser;
    SubscribePacketParser* subscribePacketParser = new SubscribePacketParser;
    parsers.insert(std::make_pair(CONNECT, connectPacketParser));
    parsers.insert(std::make_pair(DISCONNECT, disconnectPacketParser));
    parsers.insert(std::make_pair(SUBSCRIBE, subscribePacketParser));

    // FACTORIES
    std::map<PacketType,PacketFactory*> factories;
    ConnectAckPacketFactory* connectAckPacketFactory = new ConnectAckPacketFactory();
    factories.insert(std::make_pair(CONNACK, connectAckPacketFactory));
    SubAckPacketFactory* subAckPacketFactory = new SubAckPacketFactory();
    factories.insert(std::make_pair(SUBSCRIBE_ACK, subAckPacketFactory));


    ConnectionManager* connectionManager = new ConnectionManager(PORT, &parsers, &factories);
    connectionManager->serveClients();

}


