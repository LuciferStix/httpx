#include "types.h"
// #include <cstdio>
#include "request.h"
#include <sstream>
#include <string>
#include <unistd.h>
#define BUFFER 512

static std::string readline(int fd) {
  std::string line;
  char ch;

  while (read(fd, &ch, 1) > 0) {
    if (ch == '\n')
      break;
    line += ch;
  }
  return line;
}

namespace httpx {

Request frameRequest (int fd) {
  std::istringstream requestline(readline(fd));

  std::string uri;
  std::string method;
  requestline >> method >> uri;
  return {.uri = uri, .method = to_method(method)};
}

} // namespace httpx
