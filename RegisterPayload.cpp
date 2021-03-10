
#include <iostream>

using namespace std;
class RegisterPayload
{
private:
    char name[255];
    char publicKey[32];
public:
    RegisterPayload(char name[255], string publicKey){
        for (int i = 0; i < 8; i++)
        {
            this->name[i] = name[i];
        }
        
    }

    RegisterPayload(){
      
    }

    void setName(char name[255]){
        for (int i = 0; i < 255; i++)
        {
            this->name[i] = name[i];
        }
        
    }
    void setPublicKey(char publicKey[32]){
            for (int i = 0; i < 32; i++)
        {
            this->publicKey[i] = publicKey[i];
        }        
    }

    
    ~RegisterPayload();
};


