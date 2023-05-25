build:
	gcc  main.c functii.c -o lanParty -lm
clean:
	rm -f lanParty
run:
	./lanParty c.in d.in r.out