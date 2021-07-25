//
// Created by vince on 25.07.21.
//

#ifndef LMQTT__SERVER_CLIMODE_H
#define LMQTT__SERVER_CLIMODE_H

enum CLIMode{ CONNECT_MODE, SUBSCRIBE_MODE, PUBLISH_MODE, RECV_MODE };

namespace CLIModes{

    static void printUsageInformation(char* programName, PacketType mode){
        switch (mode) {
            case CONNECT_MODE:
                fprintf(stderr, "Usage: %s %s -u -p -i [-r] ip port\n", programName, PacketTypes::toString(mode));
        }
    }

    static CLIMode findCliMode(char *mode){
        if (strcmp(mode,"connect") == 0){
            return CONNECT_MODE;
        }
        fprintf(stderr,"%s","Invalid cli mode\n");
        fprintf(stderr, "valid modes are: %s, %s\n","connect","subscribe");
        exit(1);
    }
}

#endif //LMQTT__SERVER_CLIMODE_H
