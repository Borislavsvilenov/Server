#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>


class HttpServer
{
public:
  int socket_fd;
  bool active;
  std::vector<int> clients;

  HttpServer(int port);
  ~HttpServer();

  void accept_connections();
  void close_client(int client_fd);

  void read_Clients();
  std::string read_from_client(int client_fd);
  void write_to_client(int client_fd, std::string message);
};
