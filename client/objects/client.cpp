#include "client.hpp"

Client::Client(int port, std::string ip)
{
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1)
  {
    std::cerr << "Could not create socket" << std::endl;
    exit(1);
  }

  int flags = fcntl(socket_fd, F_GETFL, 0);
  fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());
  if (connect(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Error connecting to server" << std::endl;
    close(socket_fd);
    exit(1);
  }
}

Client::~Client()
{
  close(socket_fd);
}

void Client::send_message(std::string message)
{
  send(socket_fd, message.c_str(), message.size(), 0);
}

std::string Client::read_message()
{
  char buffer[1024];
  int bytes_read = recv(socket_fd, buffer, 1024, 0);
  if (bytes_read == -1)
  {
    std::cerr << "Error reading from server" << std::endl;
  }
  return std::string(buffer, bytes_read);
}
