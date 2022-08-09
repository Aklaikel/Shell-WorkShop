SRC = parser.c sh.c split.c execution.c
sh: $(SRC)
	gcc $(SRC) -o $@
re:
	rm -f sh
	@make