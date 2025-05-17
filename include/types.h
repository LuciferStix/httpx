#ifndef __HTTP_TYPES__
#define __HTTP_TYPES__

#include <string>

namespace httpx {

enum Method {
  GET,
  POST,
  // optional
  DELETE,
};
enum StatusCode {
    OK, //200
    BAD_REQUEST //404
};
std::string status_to_string(StatusCode&);


std::string method_to_string(const Method &);
Method to_method(const std::string &);

struct Request {
  std::string uri;
  Method method;
  std::string version = "HTTP/1.1";
};

struct Response {
  StatusCode status;
  std::string msg;
};


void sendResponse(int ,std::string );


 }// namespace httpx
#endif
