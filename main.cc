#include "server.h"
int main(){
    Server a;

    if (a.run() < 0 )
        printf("server band hogaya\n");
    return 0;
}
