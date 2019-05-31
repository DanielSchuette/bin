.PHONY:
	all test clean

all:
	make mario
	rm ~/bin/mario
	mv mario ~/bin
	sudo cp mario.1 /usr/local/share/man/man1/

test:
	./mario

clean:
	rm mario
