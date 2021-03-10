class RegisterSuccessPayload
{
private:
        char clientId[16];
public:

 char* getClientId(){
        return this->clientId;
    }

    RegisterSuccessPayload(/* args */);
    ~RegisterSuccessPayload();
};


