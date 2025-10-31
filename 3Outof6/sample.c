#include <stdio.h>

int main() {
	int thekey = 68;
	printf("Please enter the key: ");
	scanf_s("%d", &thekey);
	if (thekey == 68) {
		printf("Correct!\n");
	}
	else {
		printf("Incorrect\n");
	}
	return 0;
}
