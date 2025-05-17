#include "../includes/minishell.h"
#include <unistd.h>

int main(void)
{
    while (1)
    {
        char *input = get_input();
        if (!input)
            continue;
        command(input);
        free(input);
    }
    return 0;
}
