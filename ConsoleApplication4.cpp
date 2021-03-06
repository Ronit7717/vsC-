// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "aes_example.h"
#include "rsa_example.h"
#include <iostream>
#include "boost/asio.hpp"
#include "PublicKeyPayload.cpp"
#include <cstdlib>
#include <string>
#include <iostream>
#include "RegisterPayload.cpp"
#include "LittleReq.cpp"
#include <fstream>
#include "ResponseUsersList.cpp"
#include "ResponsePublicKey.cpp"
#include "ResponseGetWaitingMessages.cpp"
#include "MessagePayload.cpp"


using boost::asio::ip::tcp;
using namespace std;
using std::ifstream;


void clear(char message[], int length)
{
	for (int i = 0; i < length; i++)
		message[i] = '\0';
}

void printMenu()
{
	std::cout << "MessageU client at your service."
		<< "\n"
		<< "1) Register"
		<< "\n"
		<< "2) Request for clients list"
		<< "\n"
		<< "3) Request for public key"
		<< "\n"
		<< "4) Request for waiting messages"
		<< "\n"
		<< "5) Send a text message"
		<< "\n"
		<< "51) Send a request for symmetric key"
		<< "\n"
		<< "52) Send your symmetric key"
		<< "\n"
		<< "0) Exit client"
		<< "\n"
		<< "?"
		<< "\n";
}

//void getClientId()
//{
//	string myText;
//	int i = 0;
//	ofstream myfile("me.txt");
//	if (myfile.is_open())
//	{
//		ifstream MyReadFile("me.txt");
//		while (getline(MyReadFile, myText))
//		{
//			// Output the text from the file
//			std::cout << myText << "\n";
//			i++;
//			MyReadFile.close();
//		}
//
//		// Close the file
//	}
//	int f = i;
//}
template<class Iterator, class T>
void createGeneralHeader( T *header)
{
	char a[16] = "y6a4567fghjcvbn";
	header->setClientId(a);
	header->setVersion(2);
}

std::array<uint8_t, sizeof(LittleReq)> header1()
{
	std::array<uint8_t, sizeof(LittleReq)> buffer;
	auto *header = reinterpret_cast<LittleReq *>(buffer.data());
	//createGeneralHeader(header);
	char a[16] = "y6a4567fghjcvbn";
	header->setClientId(a);
	header->setVersion(2);
	header->setCode(100);
	header->setPayloadSize(287);
	return buffer;
}

std::array<uint8_t, sizeof(RegisterPayload)> payload1()
{
	std::array<uint8_t, sizeof(RegisterPayload)> buffer;
	auto *header = reinterpret_cast<RegisterPayload *>(buffer.data());
	char name[255] = "64f3f63985f04beb81a0e43321880182\0";
	char publicKey[32] = "user";
	header->setName(name);
	header->setPublicKey(publicKey);
	return buffer;
}

std::array<uint8_t, sizeof(LittleReq)> header2()
{
	std::array<uint8_t, sizeof(LittleReq)> buffer;
	auto *header = reinterpret_cast<LittleReq *>(buffer.data());
	//createGeneralHeader(header);
	char a[16] = "y6a4567fghjcvbn";
	header->setClientId(a);
	header->setVersion(2);
	header->setCode(101);
	header->setPayloadSize(0);
	return buffer;
}

std::array<uint8_t, sizeof(LittleReq)> header3()
{
	std::array<uint8_t, sizeof(LittleReq)> buffer;
	auto *header = reinterpret_cast<LittleReq *>(buffer.data());
	//createGeneralHeader(header);
	char a[16] = "y6a4567fghjcvbn";
	header->setClientId(a);
	header->setVersion(2);
	header->setCode(102);
	header->setPayloadSize(16);
	return buffer;
}

std::array<uint8_t, sizeof(PublicKeyPayload)> payload3()
{
	std::array<uint8_t, sizeof(PublicKeyPayload)> buffer;
	auto *header = reinterpret_cast<PublicKeyPayload *>(buffer.data());
	char clientId[16] = "64b81a0e0182\0";
	header->setClientId(clientId);
	return buffer;
}

std::array<uint8_t, sizeof(LittleReq)> header4()
{
	std::array<uint8_t, sizeof(LittleReq)> buffer;
	auto *header = reinterpret_cast<LittleReq *>(buffer.data());
	//createGeneralHeader(header);
	char a[16] = "y6a4567fghjcvbn";
	header->setClientId(a);
	header->setVersion(2);
	header->setCode(104);
	header->setPayloadSize(0);
	return buffer;
}

std::array<uint8_t, sizeof(LittleReq)> header5(int textSize)
{
	std::array<uint8_t, sizeof(LittleReq)> buffer;
	auto *header = reinterpret_cast<LittleReq *>(buffer.data());
	char a[16] = "xOwbl0UZ5lnWoBn";
	header->setClientId(a);
	header->setVersion(2);
	header->setCode(103);
	header->setPayloadSize(textSize);
	return buffer;
}

std::array<uint8_t, sizeof(MessagePayload)> payload5()
{
	std::array<uint8_t, sizeof(MessagePayload)> buffer;
	auto *header = reinterpret_cast<MessagePayload*>(buffer.data());
	char clientId[16];
	clear(clientId, 16);
	std::cout << "Enter a client name."<< "\n";
	std::cin.getline(clientId, 16); // get the client which suppose to receive the message

	header->setClientId(clientId);
	//char content[255];
	string content;
	//clear(content, 255);
	std::cout << "Enter a text message."<< "\n";
	std::cin >> content;
	unsigned char* symetricKey = createSymetricKey() ; //have to be read from file.
	string yehudit = encryptTextWithSymetricKey(content, symetricKey);

	//this parsing will be deleted after set message to unlimited string
	int n = content.length();
	int i;
	char contentChar[255] = { "\0" };
	clear(contentChar, 255);
	if (n > 255) {
		std::cout << "the message is too long" << "\n";
		return buffer;
	}
	else {
		strcpy_s(contentChar, content.c_str());

	}
	//end 
	header->setTextMessage(contentChar);
	header->setPayloadSize(255);
	header->setMessageType('3');
	return buffer;
}

string getPublicKey() {
	string pubKey = "";
	string myText;
	ifstream MyReadFile("pubKey.txt");//read private key from "privkey.txt"
	while (getline(MyReadFile, myText)) {
		pubKey += myText;
	}
	MyReadFile.close();
	return pubKey;
}

string getPrivateKey() {
	string privkey = "";
	string myText;
	ifstream MyReadFile("privkey.txt");//read private key from "privkey.txt"
	while (getline(MyReadFile, myText)) {
		privkey += myText;
	}
	MyReadFile.close();


	ofstream MyFile("me.info");//add private key to me.info (should be after name and cid)
	MyFile << privkey;
	MyFile.close();
	return privkey;
}




int main()
{
	unsigned char* yehudit = createSymetricKey();
	string s = encryptTextWithSymetricKey("hey it's ronit", yehudit);
	std::cout << "chiper text " << s << std::endl;
	string w = decryptTextWithSymetricKey(s, yehudit);
	std::cout << "dec text " << w << std::endl;


	GenKeyPair();//genrate the 2 keys. the keys saved in "privkey.txt" and "pubkey.txt"

	std::ofstream outfile("me.info");//create the file
	outfile.close();

	
	//cout << "privkey " << privkey << endl;//get private key, than after getting the cid, the saving order in me.info is:name,cid,privkey



	//unsigned char* yehudit = createSymetricKey();
	std::cout << yehudit << std::endl;
	unsigned char* ronit = createSymetricKey();
	std::cout << ronit << std::endl;
	unsigned char* zelda = createSymetricKey();
		std::cout << zelda << std::endl;

	aes_example();// create a symetric key- when somone asks
	
	PublicKeyPayload *p = new PublicKeyPayload();
    std::cout << "TOO LOdfdfs fsdfNG !\n"; 
	unsigned char * thisIsTheSymetricKey = createSymetricKey();


	char name[255] = "64f3f63985f04beb81a0e43321880182\0";
	string publicKey = "user";
	const int max_length = 1024;
	try
	{
		/*if (argc != 3)
		{
			std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
			return 1;
		}*/
	printMenu();
	boost::asio::io_context io_context;
	tcp::socket s(io_context);
	tcp::resolver resolver(io_context);

	boost::asio::connect(s, resolver.resolve("localhost", "1234"));
	std::cout << "Enter fsdfshdfi: ";
		for (;;)
		{
			std::cout << "Enter message: ";
			char request[max_length];
			clear(request, max_length);
			std::cin.getline(request, max_length);

		if ((int)request[0] - '0' == 1)
			{
				std::array<uint8_t, sizeof(LittleReq)> header = header1();
				std::array<uint8_t, sizeof(RegisterPayload)> payload = payload1();
				s.send(boost::asio::buffer(header));
				s.send(boost::asio::buffer(payload));
				std::array<uint8_t, sizeof(LittleReq)> header1;
				s.receive(boost::asio::buffer(header1));
				auto *headerdd = reinterpret_cast<LittleReq *>(header1.data());
			}

			else if ((int)request[0] - '0' == 2)
			{
				std::array<uint8_t, sizeof(LittleReq)> header = header2();
				s.send(boost::asio::buffer(header));
				std::array<uint8_t, sizeof(LittleReq)> header1;
				s.receive(boost::asio::buffer(header1));
				auto *res = reinterpret_cast<LittleReq *>(header1.data());
				int numOfUsers = res->getPayloadSize() / 271;
				for (int i = 0; i < numOfUsers; i++)
				{
					std::array<uint8_t, sizeof(ResponseUsersList)> header1;
					s.receive(boost::asio::buffer(header1));
					auto *resPayload = reinterpret_cast<ResponseUsersList *>(header1.data());
					std::cout << resPayload->getClientName() << "\n";
				}
			}

			else if ((int)request[0] - '0' == 3)
			{
				std::array<uint8_t, sizeof(LittleReq)> header = header3();
				std::array<uint8_t, sizeof(PublicKeyPayload)> payload = payload3();
				s.send(boost::asio::buffer(header));
				s.send(boost::asio::buffer(payload));
				std::array<uint8_t, sizeof(LittleReq)> header1;
				s.receive(boost::asio::buffer(header1));

				std::array<uint8_t, sizeof(ResponsePublicKey)> payloadRes;
				s.receive(boost::asio::buffer(payloadRes));
				auto *resPayload = reinterpret_cast<ResponsePublicKey *>(header1.data());
				std::cout << resPayload->getPublicKey() << "\n";
			}

			else if ((int)request[0] - '0' == 4)
			{ // ask for waiting messages. 104
				std::array<uint8_t, sizeof(LittleReq)> header = header4();
				s.send(boost::asio::buffer(header));
				std::array<uint8_t, sizeof(LittleReq)> header1;
				s.receive(boost::asio::buffer(header1));
				auto *res = reinterpret_cast<LittleReq *>(header1.data());
				int sizeOfAllMessages = res->getPayloadSize();
				while (sizeOfAllMessages)
				{
					std::array<uint8_t, sizeof(ResponseGetWaitingMessages)> message;
					s.receive(boost::asio::buffer(message));
					auto *res = reinterpret_cast<ResponseGetWaitingMessages *>(message.data());
					int messageSize = res->getMessageSize();
					sizeOfAllMessages -= messageSize;
					std::array<uint8_t, sizeof(char)> content;
					s.receive(boost::asio::buffer(content));
					auto *resContent = reinterpret_cast<char *>(content.data());
					//printMessage(resContent, res->getMessageType());
				}
			}

			else if ((int)request[0] - '0' == 5)// send a text message. code is 103. message type is 3
			{
				


				std::array<uint8_t, sizeof(MessagePayload)> payload = payload5();
				auto *payloadData = reinterpret_cast<MessagePayload*>(payload.data());
				int textSize = payloadData->getPayloadSize();
				std::array<uint8_t, sizeof(LittleReq)> header = header5(textSize);
				s.send(boost::asio::buffer(header));
				s.send(boost::asio::buffer(payload));
				std::array<uint8_t, sizeof(LittleReq)> header1;
				s.receive(boost::asio::buffer(header1));
			}










		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}










}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
