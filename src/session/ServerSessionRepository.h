#ifndef __SESSIONREPOSITORY_H__
#define __SESSIONREPOSITORY_H__

#include <FileDataManager.h>
#include "ServerSession.h"
#include "SessionRepository.h"


class ServerSessionRepository : SessionRepository<ServerSession>{
public:
    void save(ServerSession* session) override;
    ServerSession* load(char* clientId) override;

    explicit ServerSessionRepository(FileDataManager *fileDataManager);
};

#endif // __SESSIONREPOSITORY_H__