#include "request.h"
#include "router.h"
#include "server.h"
#include "types.h"
int main() {
  httpx::Router router;
  router.add(httpx::Method::GET, "/", [](const httpx::Request &a) {
    return httpx::Response("hello there");
  });

  Server a(router);

  if (a.run() < 0)
    printf("server band hogaya\n");
  return 0;
}
