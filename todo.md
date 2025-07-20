TODO fix relative paths, if a relative path is sent, dont try to search it inside $PATH, just try to execute it (Mario)
TODO make a function that inits all the crutial env variables if minishell is initd with an empty envp (Mario)
TODO export with double or single quotes does not work (Mario)
TODO unsetting PATH and trying to use command without abs/relative paths will result in core dumped, instead just ignore all non abs/relative and non builtin command calls (Mario)
TODO make all procs return values match with bash (Mario)

TODO fix double print of prompt when ctrl+c is used when a command is listening to stdin eg: cat
TODO fix memory leaks
TODO ctrl+\ after running a blocking command like cat without args should exit the shell and return 131
TODO if the line its too long it will start eating the prompt from the other side, make it so that it jumps to the next line instead
