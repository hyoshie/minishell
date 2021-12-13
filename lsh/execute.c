#include "lsh.h"
#include "execute.h"
#include "global_var.h"

static int	lsh_num_builtins(){
	return sizeof(builtin_str) / sizeof(char *);
}

/* Builtin function implementations */
int	lsh_cd(char **args)
{
	if (args[1] == NULL) {
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("lsh");
		}
	}
	return 1;
}

int	lsh_help(char **args)
{
	int	i;
	printf("hyoshie's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");
	
	for (int i = 0; i < lsh_num_builtins(); i++) {
		printf("\t%s\n", builtin_str[i]);
	}
	
	printf("Use the man command for information on other programs\n");
	return 1;
}

int	lsh_exit(char **args)
{
	exit(0);
	return 0;
}

static int	lsh_launch(char **args)
{
	pid_t	pid, wpid;
	int		status;

	pid = fork();
	if (pid == 0) {
		//Child process
		if (execvp(args[0], args) == -1) {
			perror("lsh");
		} 
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		//Error forking
		perror("lsh");
	} else {
		//Parent process
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

int	lsh_execute(char **args)
{
	int	i;

	if (args[0] == NULL) {
		// An empty command was entered.
		return 1;
	}

	for (i = 0; i < lsh_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}
	return lsh_launch(args);
}

