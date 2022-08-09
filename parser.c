#include "sh.h"



/*
text example:
minishell> ls -la | grep Makefile | wc

GRAMMAR:
<pipeline> := <cmdlist> { "|"  <cmdlist> }

<cmdlist>  := <multiple words>

*/
t_tree *parser(char **list) {
	t_tree *tree;

	tree = parse_pipeline(&list);
	if (!tree)
		fprintf(stderr, "parse error!\n");
	return tree;
}

// <pipeline> := <cmdlist>
// 			| <cmdlist> "|" <pipeline>
t_tree *parse_pipeline(char ***list) {
	// protection
	if (!*list)
		return NULL;
	
	// call <cmdlist> parser
	t_tree *ret = parse_cmdlist(list);
	if (!ret)
		return NULL;

	// { "|"  <cmdline> }   : while there is a PIPE we have to parse <cmdlist>
	while (**list && strcmp(**list, "|") == 0)
	{
		**list = NULL;

		// skipping to the next token
		(*list)++;
		
		// this is rotation
		ret = new_node(PIPE, NULL, ret, parse_cmdlist(list));

		// error
		if (!ret->right)
			return NULL;
	}
	return ret;
}

t_tree *parse_cmdlist(char ***list) {
	// creating a new node and giving it the current pointer
	// ls -la | grep Mkefile | ...
	//          ^ grep Makefile |(NULL)
	t_tree *ret = new_node(CMD, *list, NULL, NULL);
	
	// skiping the words
	while (**list && strcmp(**list, "|") != 0) {
		(*list)++;
	}

	return ret;
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