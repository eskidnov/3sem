#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateString(int n, char* string) {
	int i;
	int len;
	
	string[0] = 'a';
	for (i = 1; i < n; i++) {
		string[len] = string[0] + i;
		strncpy(string+len+1, string, len);
		len = strlen(string);
	}
	printf("%s\n", string);
}

int main() {
	int n;
	char* string;
	
	scanf("%d", &n);
	string = (char*) malloc((1<<n)*sizeof(char));
	generateString(n, string);
}
