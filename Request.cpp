#include "RegisterPayload.cpp"
using namespace std;
class Request
{
private:
    string clientId;
    int version;
    int code;
    int payloadSize;
    Payload *p;
public:

    Request(string clientId, int version, int code, int payloadSize){
    this->clientId = clientId;
    this->version = version;
    }
    Request(string clientId, int version, int code, int payloadSize,Payload *p ){
    this->clientId = clientId;
    this->version = version;
    this->code = code;
    this->payloadSize = payloadSize;
    this->p= p;

    }

    void setClientId(string clientId){
        this->clientId = clientId;
    }

      void  setVersion(int version){
        this->version = version;
    }

       void setCode(int code){
        this->code = code;
    }


      void  setPayloadSize(int payloadSize){
        this->payloadSize = payloadSize;
    }

       void setPayload(Payload *p){
        this->p = p;
    }

    Request(){

    }
    ~Request();
};

