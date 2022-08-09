#include "sh.h"

void prompt(char *cmdline)
{
	printf("minishell> ");
	fflush(stdout);
	int nbytes = read(0, cmdline, MAXSIZE);
	if (nbytes == -1)
		exit(1);
	cmdline[nbytes] = '\0';
}

int main(int ac, char **av, char **env)
{
	char   cmdline[MAXSIZE];
	char   **list = NULL;
	t_tree *tree = NULL;

	while (true)
	{
		prompt(cmdline);

		list = ft_split(cmdline, ' ');
		if (!list)
			exit(1);

		tree = parser(list);
		if (!tree)
			continue;

		disp(tree, 0);
		executor(tree);

		// free memory: list, tree...
		// free_list(list);
		free_tree(tree);
	}
}

void free_tree(t_tree *tree) {
	if (!tree)
		return ;
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
	return ;
}

void free_list(char **list) {
	for (int i = 0; list[i]; i++)
		free(list[i]);
	free(list);
}

void disp(t_tree *tree, int ident) {
	if (!tree)
		return ;
	
	for (int i = 0; i < ident; i++)
		printf("├   ");

	if (tree->type == CMD) {
		printf("├── CMD:");
		for (int i = 0; (tree->cmd)[i]; i++)
			printf(" %s", (tree->cmd)[i]);
		printf("\n");
	}

	else if (tree->type == PIPE) {
		printf("├── PIPE:\n");
	}

	disp(tree->left, ident + 1);
	disp(tree->right, ident + 1);
}