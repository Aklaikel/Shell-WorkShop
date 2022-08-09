#include "sh.h"
#include <stdio.h>
#include <unistd.h>

void	executor(t_tree *tree) {
	int fd[2];
	int pids[2];
	if (!tree){
		return ;
	}
	if (tree->type == CMD) {
		// if builtin
		//	call functions

		int pid;
		pid = fork();
		if (pid == 0) {
			// ls -la makefile
			execvp((tree->cmd)[0], tree->cmd);
			fprintf(stderr, "command not found!\n");
			exit(1);
		}

	}
	else if (tree->type == PIPE) 
		return ;
	// 	pipe(fd);
	// 	pids[0] = fork();
	// 	pids[1] = fork();
	// 	if (pids[0] == 0) {
	// 		executor(tree)
	// 		exit(0);
	// 	}
	// 	if (pids[1] == 0) {
			
	// 		exit(0);
	// 	}
	// }
}