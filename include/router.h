#ifndef __HTTP__ROUTER
#define __HTTP__ROUTER

// #include "request.h"
#include "types.h"
#include <functional>
#include <map>
#include <optional>
namespace httpx {

using routerFunc = std::function<Response(const Request &)>;

struct RouterMeta {
  Method method;
  routerFunc routerhandler;
};

class Router {
public:
  void add(const Method, const std::string &, const routerFunc &);
  Response handle(int fd);
  //{TODO} -> refractor of RouterMeta

private:
  std::map<std::string, RouterMeta> routes;
};

std::optional<Request> parse(const int &);
} // namespace httpx
#endif
