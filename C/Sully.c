#include <stdio.h>
#include <stdlib.h>

#ifndef I
#define I i
#endif

int main() {
	FILE *f;
	char name[100];
	char exec[100];
	int i = 5;
	if (i <= 0)
		return (0);

	sprintf(name, "Sully_%d.c", I);
	f = fopen(name, "w+");
	if (!f)
		return (0);

	char str[] = "#include <stdio.h>%1$c#include <stdlib.h>%1$c%1$c#ifndef I%1$c#define I i%1$c#endif%1$c%1$cint main() {%1$c	FILE *f;%1$c	char name[100];%1$c	char exec[100];%1$c	int i = %3$d;%1$c	if (i <= 0)%1$c		return (0);%1$c%1$c	sprintf(name, %2$cSully_%%d.c%2$c, I);%1$c	f = fopen(name, %2$cw+%2$c);%1$c	if (!f)%1$c		return (0);%1$c%1$c	char str[] = %2$c%4$s%2$c;%1$c	fprintf(f, str, 10, 34, I, str);%1$c	fclose(f);%1$c	sprintf(exec, %2$cgcc -DI=i-1 -o Sully_%%d Sully_%%d.c && ./Sully_%%d%2$c, I, I, I);%1$c	system(exec);%1$c	return (0);%1$c}%1$c";
	fprintf(f, str, 10, 34, I, str);
	fclose(f);
	sprintf(exec, "gcc -DI=i-1 -o Sully_%d Sully_%d.c && ./Sully_%d", I, I, I);
	system(exec);
	return (0);
}
