/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:15:42 by ahouass           #+#    #+#             */
/*   Updated: 2025/07/01 18:51:51 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
    pid_t pid;
    int pipefd[2];
    int prev_fd = -1;
    int status;
    int exit_code = 0;
    int i = 0;

    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(pipefd) == -1)
        {
            if (prev_fd != -1)
                close(prev_fd);
            return 1;
        }

        pid = fork();
        if (pid == -1)
        {
            if (prev_fd != -1)
                close(prev_fd);
            if (cmds[i + 1])
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }
            return 1;
        }

        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    exit(1);
                close(prev_fd);
            }
            if (cmds[i + 1])
            {
                close(pipefd[0]);
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                    exit(1);
                close(pipefd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }

        if (prev_fd != -1)
            close(prev_fd);
        if (cmds[i + 1])
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        i++;
    }

    while (wait(&status) != -1)
    {
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            exit_code = 1;
    }

    return exit_code;
}