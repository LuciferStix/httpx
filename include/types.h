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
  OK,         // 200
  BAD_REQUEST // 404
};

std::string status_to_string(const StatusCode &);
std::string statuscode_to_statusmsg(const StatusCode &);

std::string method_to_string(const Method &);
Method to_method(const std::string &);

struct Response {
  Response(const StatusCode &);
  Response(const std::string &);

  StatusCode status;
  std::string msg;
  std::string header;
  std::string body;
  int bodylen;
};

void handleHeader(Response &);

std::string to_string(Response &res);
void sendResponse(int, std::string);

} // namespace httpx
#endif
