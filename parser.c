#include "sh.h"

t_tree *parser(char **list) {
	(void)list;
	return new_node(PIPE, NULL, new_node(CMD, ft_split("ls", ' '), NULL, NULL), new_node(CMD, ft_split("wc", ' '), NULL, NULL));
}

t_tree *new_node(int type, char **cmd, t_tree *left, t_tree *right)
{
	t_tree *node = malloc(sizeof(t_tree));
	if (!node)
		exit(1);
	node->type = type;
	node->cmd = cmd;
	node->left = left;
	node->right = right;
	return node;
}