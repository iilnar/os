#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void handler(int signum, siginfo_t* siginfo, void* context) {
    printf("SIGUSR%d from %d\n", (signum == SIGUSR1 ? 1 : 2), siginfo->si_pid);
    exit(0);
}

int main(int charc, char** charv) {
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGUSR1);
    sigaddset(&act.sa_mask, SIGUSR2);

    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;

    if ((sigaction(SIGUSR1, &act, NULL) < 0) || (sigaction(SIGUSR2, &act, NULL) < 0)) {
        perror("Failed");
        return errno;
    } else {
        sleep(10);
        printf("No signals were caught\n");
        return 0;
    }
}
