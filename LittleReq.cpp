#include <iostream>

using namespace std;
class LittleReq
{
private:
    char clientId[16];
    char version;
    char code;
    int payloadSize;
    // Payload payload;
public:
  

 LittleReq(){
      
    }
    void setClientId(char clientId[16]){
        for (int i = 0; i < 16; i++)
        {
             this->clientId[i] = clientId[i];
        }
    
    }
    void setVersion(char version){
        this->version = version;    
    }

    void setCode(char code){
        this->code = code;    
    }

     void setPayloadSize(int payloadSize){
        this->payloadSize = payloadSize;    
    }

    int getPayloadSize(){
        return this->payloadSize; 
    }

    // void setPayload(Payload payload){
    //     this->payload = payload;    
    // }
    
    
    ~LittleReq();
};


