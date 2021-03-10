class ResponseUsersList
{
private:
     char clientId[16];
     char clientName[255];
public:

 char* getClientId(){
        return this->clientId;
    }
     char* getClientName(){
        return this->clientName;
    }

    ResponseUsersList(/* args */);
    ~ResponseUsersList();
};


