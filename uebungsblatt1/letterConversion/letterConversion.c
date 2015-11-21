#include <stdio.h>
#include <stdlib.h>

int main()
{
	char c;
	loop: printf("Enter a letter\n"); // outer loop
	get: c = getchar(); // inner loop
	if (c < 0) // EOF
		return EXIT_SUCCESS;
	if (c < 0x20 || c == 0xff) // control characters
		goto get; // repeat inner loop
	printf("%c\n", 0xff & (c ^ 0x20));
	goto loop; // repeat outer loop
}
