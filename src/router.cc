#include "router.h"

#include "types.h"
#include <optional>
#include <sstream>
#include <string>
#include <unistd.h>

namespace httpx{


    //endpoint registered
    void Router::add(const Method method, const std::string& uri, const routerFunc &func){
        routes[uri] = RouterMeta{ .method = method , .routerhandler = func};
    }

    Response Router::handle(int fd){
        // Request a =frameRequest(fd);

        //parse and get request structure
        const std::optional<Request> req = parse(fd);
        if(!req.has_value()){
            return Response(httpx::BAD_REQUEST);
        }
        const Request& request =req.value();
        if(routes.contains(request.uri)){
            RouterMeta rm = routes[request.uri];
            if(request.method == rm.method){
                return  rm.routerhandler(request);
            }
        }

            return Response(httpx::BAD_REQUEST);

    }


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

    std::optional<Request> parse(const int& fd){
        // parses and provides the request line

        std::stringstream reqline;
        reqline<<readline(fd);
        if (reqline.rdbuf()->in_avail() == 0){
            return std::nullopt ;
        }
        std::string method , uri ;
        reqline>>method>>uri;
        return Request{.method= to_method(method) , .uri=uri };

        // [LATER]
        //parse query param


    }
}
