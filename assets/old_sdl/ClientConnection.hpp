#ifndef __CLIENT_CONNECTION__
#define __CLIENT_CONNECTION__

#include "NetworkConnection.hpp"

class ClientConnection : public NetworkConnection {
protected:

public:
   ClientConnection(const char * ipAddr, int fromport, int toport);
   virtual~ClientConnection();
};

#endif
