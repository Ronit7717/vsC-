#pragma once
#include <iostream>
using namespace std;
void aes_example();

unsigned char* createSymetricKey();

string encryptTextWithSymetricKey(string text, unsigned char* symetricKey);

string decryptTextWithSymetricKey(string ciphertext, unsigned char* symetricKey);