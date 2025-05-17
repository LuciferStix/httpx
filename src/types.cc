#include "types.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
namespace httpx {

std::string method_to_string(const Method &a) {
  switch (a) {
  case Method::GET:
    return "GET";
  case Method::POST:
    return "POST";
  case Method::DELETE:
    return "DELETE";
  default:
    return "";
  }
}

Method to_method( const std::string& a){
    if(a == "GET")
        return Method::GET;
    else if (a =="POST")
        return Method::POST;
    else if(a =="DELETE")
        return Method::DELETE;
    else
        return {};
}

std::string status_to_string(StatusCode& a){
    switch(a){
        case StatusCode::OK : return "200";
        case StatusCode::BAD_REQUEST : return "404";
        default : return {};
    }
}


#define BUFFER 512
void sendResponse(int fd ,std::string msg){
    char buffer[BUFFER]={0};
    int len=msg.length();
    snprintf(buffer,BUFFER , "HTTP/1.1 200 OK\r\nContent-Length: %s\r\n\r\n%s",std::to_string(len).c_str() ,msg.c_str());
    send(fd,buffer,BUFFER,0);
}
} // namespace httpx
