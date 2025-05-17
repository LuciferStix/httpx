#include "types.h"
#include <cstdio>
#include <format>
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

std::string status_to_string(const StatusCode& a){
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

Response::Response(const StatusCode& status){
    this->status=status;
}

Response::Response(const std::string& body){
    this->body=body ;
    this->bodylen = static_cast<int>(body.length());
}

void handleHeader(Response& a ){

    a.bodylen = static_cast<int>(a.body.length());
    if(a.bodylen > 0)
        a.status =StatusCode::OK ;
    std::string header ="";
    header =std::format("Content-Length: {}\r\nContent-Type: text/plain; charset=utf-8",std::to_string(a.bodylen));
    a.header=header;
}

std::string statuscode_to_statusmsg(const StatusCode &a ){
    switch(a){
        case StatusCode::OK : return "OK";
        case StatusCode::BAD_REQUEST : return "NOT FOUND";
        default : return {};
    }
}

std::string to_string(Response& res){
    handleHeader(res);
    return std::format(
        "HTTP/1.1 {} {}\r\n{}\r\n\r\n{}",
        status_to_string(res.status),
        statuscode_to_statusmsg(res.status),
        res.header,
        res.body
    );
}

} // namespace httpx
