#include <stdio.h>
/*
	42
*/
void colleen(void) {
	return;
}

int main() {
/*
	Hi
*/
	char *s="#include <stdio.h>%c/*%c%c42%c*/%cvoid colleen(void) {%c%creturn;%c}%c%cint main() {%c/*%c%cHi%c*/%c%cchar *s=%c%s%c;%c%cprintf(s,10,10,9,10,10,10,9,10,10,10,10,10,9,10,10,9,34,s,34,10,9,10,9,10,9,10,10);%c%ccolleen();%c%creturn (0);%c}%c";
	printf(s,10,10,9,10,10,10,9,10,10,10,10,10,9,10,10,9,34,s,34,10,9,10,9,10,9,10,10);
	colleen();
	return (0);
}
