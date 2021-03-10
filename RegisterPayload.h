using namespace std;

#include "Payload.h"

class RegisterPayload : public Payload{
    public:
        RegisterPayload(){}
        RegisterPayload(char name[255] ){

            int f = 9;
        }
        RegisterPayload(char name[16], string publicKey){}

};