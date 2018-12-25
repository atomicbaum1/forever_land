#ifndef __NETWORK_CONNECTION_HPP__
#define __NETOWRK_CONNECTION_HPP__

#include <stdio.h>
#include <stdlib.h>
#include "SDLIncludes.hpp"

#define IP_ADDR_STR_SIZE 128
#define MAX_PACKET_SIZE 512

enum NetworkDataType {
   NetworkDataType_Hello = 0,
   NetworkDataType_Goodbye,
};

struct NetworkData {
   NetworkDataType dataType;
   unsigned int id;
   unsigned int requestNo;
   unsigned int dataLength;
   void * data;
};

class NetworkConnection {
protected:
   UDPsocket _socket;
   IPaddress _address;
   UDPpacket * _packet;
   char _ipAddressStr[IP_ADDR_STR_SIZE];
   int _portNumber;

public:
   NetworkConnection(const char * ipAddr, int fromport, int toport);
   virtual ~NetworkConnection();
   void connect();
   void disconnect();
   virtual void sendData(NetworkData * data);
   NetworkData * receiveData();
};

#endif
