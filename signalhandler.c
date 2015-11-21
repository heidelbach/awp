
#include <signal.h> // sigaction(int, struct sigaction *, struct sigaction *), struct sigaction, Makros für Signale
#include <stdio.h> // fprintf(int, char *...), printf(char *...)
#include <unistd.h> // int pause(void)

struct sigaction actionNew;

void mySigHandler(int signal)
{
	printf("\rCaught signal %d\n", signal);
}

int main()
{
	sigemptyset(&actionNew.sa_mask);
	actionNew.sa_flags = 0;	
	actionNew.sa_handler = mySigHandler;
	
	if (sigaction(SIGINT, &actionNew, NULL))
	{
		fprintf(stderr, "Error installing handler for SIGINT\n");
	}
	if (sigaction(SIGUSR1, &actionNew, NULL))
	{
		fprintf(stderr, "Error installing handler for SIGUSR1\n");
	}
	if (sigaction(SIGUSR2, &actionNew, NULL))
	{
		fprintf(stderr, "Error installing handler for SIGUSR2\n");
	}
	if (sigaction(SIGTERM, &actionNew, NULL))
	{
		fprintf(stderr, "Error installing handler for SIGTERM\n");
	}
	if (!sigaction(SIGSTOP, &actionNew, NULL))
	{
		fprintf(stderr, "Error installing handler for SIGSTOP - it did not failed!\n");
		return 1;
	}
	if (sigaction(SIGCONT, &actionNew, NULL))
	{
		fprintf(stderr, "Error installing handler for SIGCONT\n");
	}
	while(1)
		pause();

}
