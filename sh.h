#ifndef SH_H
#define SH_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define MAXSIZE 1024
#define PIPE 1
#define CMD 2

typedef struct s_tree
{
	int type;
	char **cmd;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;


char	**ft_split(char const *s, char c);
t_tree  *new_node(int type, char **cmd, t_tree *left, t_tree *right);
t_tree  *parser(char **list);
void    executor(t_tree *tree);
void 	free_tree(t_tree *tree);
void 	free_list(char **list);

#endif