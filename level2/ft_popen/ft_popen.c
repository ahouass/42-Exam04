/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:25 by ahouass           #+#    #+#             */
/*   Updated: 2025/06/05 14:31:28 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int		fds[2];
	pid_t	pid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;
	if(pipe(fds) == -1)
		return -1;
	pid = fork();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return -1;
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			dup2(fds[1], 1);
		}
		else
		{
			dup2(fds[0], 0);
		}
		close(fds[0]);
		close(fds[1]);
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(fds[1]);
		return (fds[0]);
	}
	if (type == 'w')
	{
		close(fds[0]);
		return (fds[1]);
	}
	return -1;
}

int main()
{
    int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, 0);
	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
    char line[999999];

    read(fd, line, 100);
	line[100] = '\0';
    puts(line);
    return (0);
}