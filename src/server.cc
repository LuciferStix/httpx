#include "ess_imports.h"
#include <cstdlib>
#include <print>
#include <sys/socket.h>
#include <unistd.h>
#include "types.h"
#include "router.h"
void Server::setAddr(std::string addr = "0.0.0.0") { this->_addr = addr; }
void Server::setPort(int port = 8080) {
  this->_port = port;
}
Server::Server() {
    init();
}
Server::Server(const httpx::Router &router){
    init();
    _router=router;
}

void Server::init(){
    _run = true;
    _socketfd = 0;
    _servermeta = {
        .sin_family = AF_INET,
    };
    this->setAddr();
    this->setPort();
}

void handler(int sig) {
  switch (sig) {
  case SIGINT:
    printf("[#] signal interrupt...\n");
    break;
  case SIGTERM:
    printf("[#] signal termination ...\n");
    break;
  case SIGKILL:
    printf("[#] signal kill ... \n");
    break;

  default:
    printf("unknown signal encountered ....\n");
    break;
  }
  printf("shutting down....\n");
  exit(EXIT_FAILURE);
}

int Server::run() {
  std::signal(SIGINT, handler);

  // socket creation
  _socketfd = socket(AF_INET, SOCK_STREAM, 0);

  // reusable socket
  int optval = 1;
  socklen_t optval_len = sizeof(optval);
  if (setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR, &optval, optval_len) < 0)
    perror(std::strerror(errno));

  _servermeta.sin_port = htons(_port);
  _servermeta.sin_addr.s_addr = inet_addr(_addr.c_str());
  _len = sizeof(_servermeta);

  printf("[#]binding...\n");
  if (!bind(_socketfd, (const struct sockaddr *)&_servermeta, _len))
    perror(strerror(errno));

  printf("[#]Listening..\n");
  if (listen(_socketfd, 5) < 0)
    perror(strerror(errno));

  while (_run) {
    int _acceptfd = accept(_socketfd, (struct sockaddr *)&_servermeta, &_len);
    // httpx::Request reqline=httpx::frameRequest(_acceptfd);
    // httpx::sendResponse(_acceptfd,"namaste india!!!");

    httpx::Response res = _router.handle(_acceptfd);
    std::println("response: \n{}",httpx::to_string(res));
    std::string response= httpx::to_string(res);
    write(_acceptfd,response.c_str(), sizeof(response));
    close(_acceptfd);
  }

  return 1;
}
