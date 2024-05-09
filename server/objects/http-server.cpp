#include "http-server.hpp"

HttpServer::HttpServer(int port)
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
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  if (bind(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Error binding socket" << std::endl;
    close(socket_fd);
    exit(1);
  }

  listen(socket_fd, 5);

  active = true;
}

HttpServer::~HttpServer()
{
  close(socket_fd);
  for (int i = 0; i < clients.size(); i++)
  {
    close(clients[i]);
  }
  active = false;
}

void HttpServer::accept_connections()
{
  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  int client_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_addr_len);
  if (client_fd == -1)
  {
    std::cerr << "Error accepting connection" << std::endl;
  } else {
    clients.push_back(client_fd);
    std::cout << "Client connected" << std::endl;
  }
}

void HttpServer::close_client(int client_fd)
{
  close(client_fd);
  clients.erase(std::remove(clients.begin(), clients.end(), client_fd), clients.end());
}

void HttpServer::read_Clients()
{
  for (int i = 0; i < clients.size(); i++)
  {
    read_from_client(clients[i]);
  }
}

std::string HttpServer::read_from_client(int client_fd)
{
  char buffer[1024];
  int bytes_read = recv(client_fd, buffer, 1024, 0);
  if (bytes_read == -1)
  {
    std::cerr << "Error reading from client" << std::endl;
  }
  else if(bytes_read == 0)
  {
    close_client(client_fd);
    std::cout << "Client disconnected" << std::endl;
  }
  std::cout << "Client sent: " << buffer << std::endl;
  return std::string(buffer, bytes_read);
}

void HttpServer::write_to_client(int client_fd, std::string message)
{
  send(client_fd, message.c_str(), message.size(), 0);
}
