#include <unistd.h>
#include <signal.h>

void handler(int param) {}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigaction(SIGTERM, &sa, 0);

    pause();
    
    return 0;
}
