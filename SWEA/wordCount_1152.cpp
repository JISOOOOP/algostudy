#include <iostream>

using namespace std;

int main() {

	int spaceCount = 1;
	char temp = getc(stdin);
	char before = temp;
	
	while ((temp = getc(stdin)) != '\n') {
		if (temp == ' ') ++spaceCount;
		before = temp;
	}
	if (before == ' ') --spaceCount;
	printf("%d", spaceCount);
}