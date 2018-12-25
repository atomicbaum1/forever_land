#include "ServerConnection.hpp"

ServerConnection::ServerConnection(const char * ipAddr, int fromport, int toport) :
   NetworkConnection(ipAddr, fromport, toport) {

}

ServerConnection::~ServerConnection() {

}
