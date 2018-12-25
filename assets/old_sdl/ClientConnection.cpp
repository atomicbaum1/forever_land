#include "ClientConnection.hpp"

ClientConnection::ClientConnection(const char * ipAddr, int fromport, int toport) :
   NetworkConnection(ipAddr, fromport, toport) {

}

ClientConnection::~ClientConnection() {

}
