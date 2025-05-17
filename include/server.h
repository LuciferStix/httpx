
#include <string>
// #include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>

// struct sockaddr_in;

class Server {
public:
  Server();

  Server *setPort(int);
  void setAddr(std::string);
  [[nodiscard]]
  int run();

private:
  int _socketfd;
  // error of forward declaration
  std::string _addr;
  uint16_t _port;
  bool _run;
  struct sockaddr_in _servermeta;
  socklen_t _len;
};
