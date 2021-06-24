//
// Created by vince on 24.06.21.
//

#ifndef LMQTT__SERVER_SESSIONREPOSITORY_H
#define LMQTT__SERVER_SESSIONREPOSITORY_H

template<class S>
class SessionRepository{
protected:
    FileDataManager* _fileDataManager;
public:
    virtual void save(S* session) = 0;
    virtual S* load(char* clientId) = 0;
};

#endif //LMQTT__SERVER_SESSIONREPOSITORY_H
