NAME = minishell

SRC = parser.c sh.c split.c execution.c
$(NAME): $(SRC)
	gcc $(SRC) -o $@
re:
	rm -f $(NAME)
	@make