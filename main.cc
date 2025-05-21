// #include "request.h"
#include "router.h"
#include "server.h"
#include "types.h"
int main() {
  httpx::Router router;

  router.add(httpx::Method::GET, "/", [](const httpx::Request &a) {
    return httpx::Response("GAWWWWKWKKKK");
  });



  router.add(httpx::Method::GET, "/noice", [](const httpx::Request &a) {
    return httpx::Response("yoo NIGAAA");
  });
  Server a(router);

  if (a.run() < 0)
    printf("server band hogaya\n");
  return 0;
}
