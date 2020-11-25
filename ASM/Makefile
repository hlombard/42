NAME = Colleen Grace Sully

CC = clang

COLLEEN_SRC=Colleen.s
GRACE_SRC=Grace.s
SULLY_SRC=Sully.s

COLLEEN_OBJ=$(COLLEEN_SRC:.s=.o)
GRACE_OBJ=$(GRACE_SRC:.s=.o)
SULLY_OBJ=$(SULLY_SRC:.s=.o)

all: $(NAME)

%.o:%.s
	@nasm -f elf64 $< -dOFFSET=1

Colleen: $(COLLEEN_OBJ)
	@$(CC) $(COLLEEN_OBJ) -o Colleen

Grace: $(GRACE_OBJ)
	@$(CC) $(GRACE_OBJ) -o Grace

Sully: $(SULLY_OBJ)
	@$(CC) $(SULLY_OBJ) -o Sully

clean:
	@rm -f $(COLLEEN_OBJ)
	@rm -f $(GRACE_OBJ)
	@rm -f $(SULLY_OBJ)
	@rm -f Sully*.o

fclean: clean
	@rm -f Colleen
	@rm -f Grace
	@rm -f Sully
	@rm -f Sully_* Grace_kid.s

re: fclean all
