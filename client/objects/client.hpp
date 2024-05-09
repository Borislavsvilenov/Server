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

class Client
{
public:
  int socket_fd;
  
  Client(int port, std::string ip);
  ~Client();
  
  void send_message(std::string message);
  std::string read_message();
};
