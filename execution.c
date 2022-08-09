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
	else if (tree->type == PIPE) {
		pipe(fd);
		pids[0] = fork();
		if (pids[0] == 0) {
			close(1);
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			executor(tree->left);
			exit(0);
		}
		pids[1] = fork();
		if (pids[1] == 0) {
			close(0);
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			executor(tree->right);
			exit(0);
		}
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}
}