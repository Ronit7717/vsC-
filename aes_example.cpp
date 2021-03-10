#include "pch.h"
#include <modes.h>
#include <aes.h>
#include <filters.h>
#include "pch.h"
#include <iostream>
#include <string>
#include <immintrin.h>	// _rdrand32_step

#include "aes_example.h"

using namespace std;
// size must be a 4 bytes align.
char* generate_key(char* buff, size_t size)
{
	for (size_t i = 0; i < size; i += 4)
		_rdrand32_step(reinterpret_cast<unsigned int*>(&buff[i]));
	std::cout << "buffi" << typeid(buff).name() << std::endl;
	return buff;
}

char* yehudit() {
	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
	memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

	char* buff = generate_key(reinterpret_cast<char*>(key), CryptoPP::AES::DEFAULT_KEYLENGTH);
	char* buff1 = generate_key(reinterpret_cast<char*>(key), CryptoPP::AES::DEFAULT_KEYLENGTH);
	std::cout << buff << std::endl;
	std::cout << buff1 << std::endl;
	return reinterpret_cast<char*>(key);
}

 unsigned char* createSymetricKey() {
	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
	memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

	 char* buff = generate_key(reinterpret_cast<char*>(key), CryptoPP::AES::DEFAULT_KEYLENGTH);
	std::cout << buff << std::endl;
	return key;
}

string encryptTextWithSymetricKey(string text, unsigned char* symetricKey) {
	std::string ciphertext;

	CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

	CryptoPP::AES::Encryption aesEncryption(symetricKey, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(text.c_str()), text.length());
	stfEncryptor.MessageEnd();


	return ciphertext;
}

string decryptTextWithSymetricKey(string ciphertext, unsigned char* symetricKey) {
	string decryptedtext;
	CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);
	CryptoPP::AES::Decryption aesDecryption(symetricKey, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size());
	stfDecryptor.MessageEnd();

	return decryptedtext;
}

void aes_example()
{
	std::cout << "=== AES EXAMPLE ===" << std::endl;
	createSymetricKey();

	char* h = yehudit();
	std::cout << h << std::endl;
	std::cout << &h << std::endl;
	std::cout << *h << std::endl;
		char* hh = yehudit();

	// Key and IV setup
	// AES encryption uses a secret key of  a variable length (128-bit, 196-bit or 256-bit).
	// This key is secretly exchanged between two parties before communication begins.
	//
	CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
	memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

	generate_key(reinterpret_cast<char*>(key), CryptoPP::AES::DEFAULT_KEYLENGTH);

	//td::cout << key << std::endl;
	std::cout << typeid(key).name() << std::endl;


	std::string plaintext = "Hello from crypto++. Whatsapp?";
	std::string ciphertext;
	std::string decryptedtext;

	std::cout << "Plain text:" << std::endl;
	std::cout << plaintext << std::endl;

	// create cipher text
	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length());
	stfEncryptor.MessageEnd();


	std::cout << "cipher text:" << std::endl;
	for (size_t i = 0; i < ciphertext.size(); i++)
	{
		std::cout << "0x" << std::hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
	}
	std::cout << std::endl << std::endl;


	// decrypt
	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size());
	stfDecryptor.MessageEnd();

	std::cout << "decrypt test:" << std::endl;
	std::cout << decryptedtext;
	std::cout << std::endl;
	//return key;
}

char* EncryptionSymmetricKey() {// encrypt message with symmetric key
	std::cout << "=== EncryptionSymmetricKey ===" << std::endl;
	char word[] = "hey EncryptionSymmetricKey";
	return word;
}

/*char* decipheringSymmetricKey() {//decrypt message with symmetric key 
	std::cout << "=== decipheringSymmetricKey ===" << std::endl;
	char word[] = "hey decipheringSymmetricKey";
	return word;
}

char* getNewSymmetricKey() {//generate new symmetric key to send to user that asked it
	std::cout << "=== getNewSymmetricKey ===" << std::endl;
	char word[] = "hey getNewSymmetricKey";
	return word;

}*/