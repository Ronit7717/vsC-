class ResponseGetWaitingMessages
{
private:
    char clientId[16];
    char messageId[4];
    char messageType;
    int messageSize;
public:
 char* getClientId(){
        return this->clientId;
    }
     char* getMessageId(){
        return this->messageId;
    }
     char getMessageType(){
        return this->messageType;
    }

     int getMessageSize(){
        return this->messageSize;
    }



    ResponseGetWaitingMessages(/* args */);
    ~ResponseGetWaitingMessages();
};


