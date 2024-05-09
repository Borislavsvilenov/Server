#include "objects/client.hpp"

int main()
{
  Client *client = new Client(8080, "127.0.0.1");
  client->send_message("Hello, server!");
  std::cout << client->read_message() << std::endl;
  return 0;
}


