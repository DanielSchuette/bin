# Makefile for make_hex
BIN = make_hex
BIN_DIR = ~/bin
MAN = $(BIN).1

all:
	make $(BIN)
	@(rm $(BIN_DIR)/$(BIN) 2>/dev/null && echo 'Removed old version.') || \
		echo 'No old version found.'
	mv $(BIN) $(BIN_DIR)
	sudo cp $(MAN) /usr/local/share/man/man1/

test:
	./$(BIN)

clean:
	rm $(BIN)

.PHONY:
	all test clean
