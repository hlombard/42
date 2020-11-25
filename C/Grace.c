#include <stdio.h>
/*
	This is crazy
*/
#define ERROR return(1)
#define STR "#include <stdio.h>%c/*%c%cThis is crazy%c*/%c#define ERROR return(1)%c#define STR %c%s%c%c#define FT(x)int main(){FILE *f; if(!(f = fopen(x, %cw%c)))ERROR;fprintf(f, STR,10,10,9,10,10,10,34,STR,34,10,34,34,10,34,34,10);}%cFT(%cGrace_kid.c%c)%c"
#define FT(x)int main(){FILE *f; if(!(f = fopen(x, "w")))ERROR;fprintf(f, STR,10,10,9,10,10,10,34,STR,34,10,34,34,10,34,34,10);}
FT("Grace_kid.c")
