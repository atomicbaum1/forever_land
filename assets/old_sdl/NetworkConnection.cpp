#include "NetworkConnection.hpp"
#include <string>

NetworkConnection::NetworkConnection(const char * ipAddr, int fromport, int toport) {
   memcpy(_ipAddressStr, ipAddr, sizeof _ipAddressStr);
   _portNumber = toport;

   if ((_packet = SDLNet_AllocPacket(MAX_PACKET_SIZE)) == NULL) {
      printf("Error allocating packet\n");
      // TODO: Throw error
      return;
   }
   printf("Open port %d\n", fromport);
   if ((_socket = SDLNet_UDP_Open(fromport)) == NULL) {
      printf("Error opening port\n");
      // TODO: Throw error
      return;
   }
}

NetworkConnection::~NetworkConnection() {
   disconnect();
   SDLNet_FreePacket(_packet);
}

void NetworkConnection::connect() {
   if (SDLNet_ResolveHost(&_address, _ipAddressStr, _portNumber) < 0) {
      printf("Error connecting\n");
      return;
      // TODO: Throw error
   }
   _packet->address.host = _address.host;
   _packet->address.port = _address.port;
}

void NetworkConnection::disconnect() {
   SDLNet_UDP_Close(_socket);
}

void NetworkConnection::sendData(NetworkData * data) {
   static int headerLength = (sizeof(NetworkData)) - (sizeof(void *));
   int totalLength = headerLength + data->dataLength;
   if (totalLength > MAX_PACKET_SIZE) {
      printf("Error making packet\n");
      // TODO: Throw error
      return;
   }
   memcpy(_packet->data, data, headerLength);
   memcpy(_packet->data + headerLength, data->data, data->dataLength);
   _packet->len = totalLength;

   if (SDLNet_UDP_Send(_socket, -1, _packet) == 0) {
      printf("Error sending packet\n");
      // TODO: Throw error
      return;
   }
}

NetworkData * NetworkConnection::receiveData() {
   static NetworkData data;
   static int headerLength = (sizeof(NetworkData)) - (sizeof(void *));
   NetworkData * ptr;

   if (SDLNet_UDP_Recv(_socket, _packet)) {
      ptr = (NetworkData *)_packet->data;
      memcpy(&data, ptr, headerLength);
      data.data = &ptr->data;
      return &data;
   }
   return NULL;
}
