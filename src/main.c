#include "../includes/minishell.h"
#include "miniutils/miniutils.h"
#include <stdio.h>
#include <unistd.h>


int g_status;

t_prompt set_initial_variables(char **argv, char **envp)
{
   t_prompt prompt;
   prompt.input = NULL;
   prompt.envp = matrix_str_dup(envp, -1, NULL);
   //TODO get pid for the minishell process
   //TODO initialize essential variables
   return prompt;
}

t_prompt initialize_variables(t_prompt prompt, char *str, char **argv)
{

}

int main(int argc, char **argv, char **envp)
{
    (void) argc; // Not in use right now
    t_prompt prompt;
    prompt = set_initial_variables(argv, envp);
    /* char **dup =  matrix_str_dup(prompt.envp); */
    /* dup = matrix_str_add(dup, "hello"); */
    /* matrix_str_print(dup); */
    int i = 0;
    int j = 1;
    char **matrix;
    while (1)
    {
        char *input = get_input();
        if (!input)
            continue;
        command(input, &prompt.envp);
        /* is_in_envp("hi", prompt.envp); */
        /* matrix =  matrix_str_add(prompt.envp, "hello"); */
        free(input);
    }
    return 0;
}


/* int main(int argc, char **argv, char **envp) */
/* { */
/* 	(void)argc; */
/* 	(void)argv; */
/*     char **myenvp = matrix_str_dup(envp, -1, NULL); */
/*     char **command = ft_split("unset KEYTIMEO=", ' '); */
/*     builtin_unset(command, &myenvp); */
/*     /\* int var_position; *\/ */
/*     /\* int i = 1; *\/ */
/* 	/\* var_position = is_in_envp(command[1], myenvp); // search var inside envp *\/ */
/* 	/\* printf("%d\n", var_position); *\/ */
/*     /\* builtin_export(command, &myenvp); *\/ */
/*     /\* int nline = is_in_envp("STARSHIP_SHELL", myenvp); *\/ */
/*     /\* printf("%d\n", nline); *\/ */
/*     /\* myenvp = matrix_str_dup(myenvp, nline, NULL); *\/ */
/*     matrix_str_print(myenvp); */
/*     /\* matrix_free(&myenvp); *\/ */
/* 	/\* char *name = get_var_name("KEYTIMEOUT"); *\/ */
/*     /\* printf("%s\n", name); *\/ */
/*     /\* free(name); *\/ */
/* } */
