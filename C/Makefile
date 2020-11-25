CC= gcc

FLAG= -Wall -Werror -Wextra

SRC_COLLEEN=Colleen.c
SRC_GRACE=Grace.c
SRC_SULLY=Sully.c

OBJ_COLLEEN=$(SRC_COLLEEN:.c=.o)
OBJ_GRACE=$(SRC_GRACE:.c=.o)
OBJ_SULLY=$(SRC_SULLY:.c=.o)

all: Colleen Grace Sully

Colleen: $(OBJ_COLLEEN)
	@$(CC) $(FLAG) $(OBJ_COLLEEN) -o Colleen

Grace: $(OBJ_GRACE)
	@$(CC) $(FLAG) $(OBJ_GRACE) -o Grace

Sully: $(OBJ_SULLY)
	@$(CC) $(FLAG) $(OBJ_SULLY) -o Sully

%.o: %.c
	@$(CC) $(FLAG) -o $@ -c $<

clean:
	@rm -f $(OBJ_COLLEEN)
	@rm -f $(OBJ_GRACE)
	@rm -f $(OBJ_SULLY)

fclean: clean
	@rm -f Colleen 
	@rm -f Grace
	@rm -f Sully
	@rm -f Sully_* Grace_kid.c

re: fclean all

.PHONY: all clean fclean re
