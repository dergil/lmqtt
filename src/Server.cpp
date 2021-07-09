#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

#include "io/PacketIOManager.h"
#include "packets/ConnectPacket.h"
#include "packets/parsers/PacketParser.h"
#include "packets/parsers/ConnectPacketParser.h"
#include "handlers/ConnectPacketHandler.h"
#include "handlers/PacketHandler.h"
#include "con/ServerConnection.h"
#include "util/Utils.h"
#include "files/FileDataManager.h"


#define PORT 8080

static int waitForConnection(){
    int server_fd, conn_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((conn_socket = accept(server_fd, (struct sockaddr *)&address,
                              (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    return conn_socket;
}

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
    // PARSERS
    std::map<PacketType,PacketParser*> parsers;
    ConnectPacketParser* connectPacketParser = new ConnectPacketParser;
    parsers.insert(std::make_pair(CONNECT, connectPacketParser));

    // FACTORIES
    ConnectAckPacketFactory* connectAckPacketFactory = new ConnectAckPacketFactory();


    while (true){
        std::cout << "waiting for new connection" << "\n";
        int connFd = waitForConnection();
        std::cout << "connected to client" << "\n";
        ServerConnection* connection = new ServerConnection();
        PacketIOManager* packetIO = new PacketIOManager(connection,connFd, &parsers);
        FileDataManager* fileDataManager = new FileDataManager();

        // HANDLERS
        std::map<PacketType,PacketHandler*> handlers;
        ServerSessionRepository* serverSessionRepository = new ServerSessionRepository(fileDataManager);
        ConnectPacketHandler* connectPacketHandler = new ConnectPacketHandler(connection,packetIO,connectAckPacketFactory, serverSessionRepository);
        handlers.insert(std::make_pair(CONNECT, connectPacketHandler));

        while(true){
            try{
                std::cout << "waiting for new packet" << "\n";
                RawPacket* packet = packetIO->readPacket();
                PacketHandler* handler = handlers[packet->getType()];
                handler->handle(packet);
                std::cout << "packet handled without errors" << "\n";
            } catch (const std::exception& e) {
                std::cout << "exception occurred:" << "\n";
                std::cout << e.what() << "\n";
                packetIO->closeConnection();
                delete connection;
                break;
            }
        }
    }
}