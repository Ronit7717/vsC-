#include "pch.h"

#include <rsa.h>
#include <osrng.h>
#include <base64.h>
#include <files.h>
#include <string>
#include <fstream>

#include "rsa_example.h"

// This example generate key pair (private and public) and then saves them to disk in base64 format
void GenKeyPair()
{

	// InvertibleRSAFunction is used directly only because the private key
	// won't actually be used to perform any cryptographic operation;
	// otherwise, an appropriate typedef'ed type from rsa.h would have been used.
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction privkey;
	privkey.Initialize(rng, 1024);

	// With the current version of Crypto++, MessageEnd() needs to be called
	// explicitly because Base64Encoder doesn't flush its buffer on destruction.
	CryptoPP::Base64Encoder privkeysink(new CryptoPP::FileSink("privkey.txt"));
	privkey.DEREncode(privkeysink);
	//privkeysink.MessageEnd();

	// Suppose we want to store the public key separately,
	// possibly because we will be sending the public key to a third party.
	CryptoPP::RSAFunction pubkey(privkey);

	CryptoPP::Base64Encoder pubkeysink(new CryptoPP::FileSink("pubkey.txt"));
	pubkey.DEREncode(pubkeysink);
	pubkeysink.MessageEnd();
	std::cout <<"the privkey"<< typeid(privkey).name() << std::endl;
	std::cout << "the pubkey" << typeid(pubkey).name() << std::endl;
	std::cout << "the pubkey len" << sizeof(pubkey) << std::endl;
	//std::cout << "the pubkey is" << pubkey.GetIntValue << std::endl;
}

// This example loads a private key, and generates it's public counterpart
void LoadAndGenPublicKey()
{
	CryptoPP::ByteQueue bytes;
	CryptoPP::FileSource file("privkey.txt", true, new CryptoPP::Base64Decoder);
	file.TransferTo(bytes);
	bytes.MessageEnd();
	CryptoPP::RSA::PrivateKey privateKey;
	privateKey.Load(bytes);
	std::cout << "the bytes" << sizeof(bytes) << std::endl;

	CryptoPP::RSAFunction pubkey(privateKey);
	CryptoPP::Base64Encoder pubkeysink(new CryptoPP::FileSink("pubkey2.txt"));
	pubkey.DEREncode(pubkeysink);
	pubkeysink.MessageEnd();
	//std::cout << "the privkey" << typeid(privateKey).name() << std::endl;
	//std::cout << "the pubkey" << typeid(pubkey).name() << std::endl;

}


// this example loads a public key into a buffer. then uses that buffer to encrypt a message
void EncryptDecryptWithBuffer(std::string message)
{
	// plain text

	CryptoPP::AutoSeededRandomPool rng;

	//Read public key
	CryptoPP::ByteQueue bytes;
	CryptoPP::FileSource file("pubkey.txt", true, new CryptoPP::Base64Decoder);
	file.TransferTo(bytes);
	bytes.MessageEnd();
	CryptoPP::RSA::PublicKey pubKey;
	pubKey.Load(bytes);


	// Save the key to an unsigned char buffer.
	// Note on key size: We use 160 character here becuase our key is 1024 bits in size (the actual public key contains more data then just "the key")
	// In a real world scenario we would have used different key sizes and thus, using a dynamic buffer (vector, or even an std::string)
	static const size_t KEYSIZE = 160;
	CryptoPP::byte buf[KEYSIZE];
	CryptoPP::ArraySink as(buf, KEYSIZE);
	pubKey.Save(as);


	// copy the buffer to a different variable
	CryptoPP::byte buf2[KEYSIZE];
	memcpy(buf2, buf, KEYSIZE);
	CryptoPP::ArraySource as2(buf2, KEYSIZE, true);

	CryptoPP::RSA::PublicKey pubKey2;
	pubKey2.Load(as2);


	// encrypt (using public key)
	std::string ciphertext;
	CryptoPP::RSAES_OAEP_SHA_Encryptor e(pubKey2);
	CryptoPP::StringSource ss(message, true, new CryptoPP::PK_EncryptorFilter(rng, e, new CryptoPP::StringSink(ciphertext)));


	// prints out the cipher text (since it is encrypted and probably contains non-printable characters, we display hex values)
	std::cout << "cipher text:" << std::endl;
	for (size_t i = 0; i < ciphertext.size(); i++)
	{
		std::cout << "0x" << std::hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i])) << " ";
	}
	std::cout << std::endl;


	//Read private key
	{
		CryptoPP::ByteQueue bytes;
		CryptoPP::FileSource file("privkey.txt", true, new CryptoPP::Base64Decoder);
		file.TransferTo(bytes);
		bytes.MessageEnd();
		CryptoPP::RSA::PrivateKey privateKey;
		privateKey.Load(bytes);

		// decrypt
		std::string decrypted;
		CryptoPP::RSAES_OAEP_SHA_Decryptor d(privateKey);
		CryptoPP::StringSource ss(ciphertext, true, new CryptoPP::PK_DecryptorFilter(rng, d, new CryptoPP::StringSink(decrypted)));
		std::cout << "decrypted:" << decrypted << std::endl;
	}
}

void rsa_example(std::string message)
{
	std::cout << "=== RSA EXAMPLE ===" << std::endl;

	GenKeyPair();

	LoadAndGenPublicKey();

	EncryptDecryptWithBuffer(message);
}

