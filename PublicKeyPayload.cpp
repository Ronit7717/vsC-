#include "pch.h"

#include <iostream>

using namespace std;
class PublicKeyPayload
{
private:
    char clientId[16];
public:
    PublicKeyPayload(){
      
        
    }

	void yehudit() {
		std::cout << "Enter message: ";

	}

    void setClientId(char clientId[16]){
        for (int i = 0; i < 16; i++)
        {
            this->clientId[i] = clientId[i];
        } 
    }
        
    

    
    ~PublicKeyPayload();
};


