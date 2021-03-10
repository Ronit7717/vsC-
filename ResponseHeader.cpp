class ResponseHeader
{
private:
    char version;
    char code;
    int payloadSize;
public:

    char getVersion(){
        return this->version;
    }

    char getCode(){
        return this->code;
    }


    int getPayloadSize(){
        return this->payloadSize;
    }




    ResponseHeader(/* args */);
    ~ResponseHeader();
};
