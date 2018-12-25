#ifndef __SERVER_CONNECTION_HPP__
#define __SERVER_CONNECTION_HPP__

#include "NetworkConnection.hpp"

class ServerConnection : public NetworkConnection {
protected:

public:
   ServerConnection(const char * ipAddr, int fromport, int toport);
   virtual ~ServerConnection();
};

#endif
