NAME= dr-quine

all: Grace Colleen Sully

Grace:
	@go build Grace.go

Colleen:
	@go build Colleen.go

Sully:
	@go build -ldflags "-X main.offset=TRUE" Sully.go

clean:
	@rm -f Colleen
	@rm -f Grace
	@rm -f Sully
	@rm -f Sully_* Grace_kid.go

fclean: clean

re: fclean all

