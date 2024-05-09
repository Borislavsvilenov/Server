#include "objects/http-server.hpp"

int main()
{
  HttpServer *server = new HttpServer(8080);

  while (server->active)
  {
    server->accept_connections();
    server->read_Clients();
    sleep(1);
  }

  return 0;
}
