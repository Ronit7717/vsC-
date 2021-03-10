class TextMessagePayload
{
private:
    char clientId[16];
    char textMessage[255];
public:
        void setClientId(char clientId[16]){
        for (int i = 0; i < 16; i++)
        {
             this->clientId[i] = clientId[i];
        }
    
    }

    void setTextMessage(char text[255]){
        int i = 0;
         for (i; i < 255; i++)
        {
             this->textMessage[i] = text[i];
        }
         this->textMessage[i] = '\0';
    }

    int getPayloadSize (){
        return 255;
        }


    TextMessagePayload(/* args */);
    ~TextMessagePayload();
};

