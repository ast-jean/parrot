

all: parrot

real_parrot:
	@curl parrot.live

rev:
	@rev

fish:
	@./asciiquarium

parrot: gcc_parrot
	./parrot

gcc_parrot:
	gcc parrot.c -o parrot