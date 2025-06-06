/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_popen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:41:19 by ahouass           #+#    #+#             */
/*   Updated: 2025/06/06 12:09:14 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	pid_t		pid;
	int			fds[2];
	
	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;
	if (pipe(fds) == -1)
		return -1;
	pid = fork();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return -1;
	}
	if(pid == 0)
	{
		if(type == 'r')
		{
			dup2(fds[1], 1);
		}
		if(type == 'w')
		{
			dup2(fds[0], 0);
		}
		close(fds[0]);
		close(fds[1]);
		execvp(file, argv);
		exit(1);
	}
	if(type == 'r')
	{
		close(fds[1]);
		return (fds[0]);
	}
	if(type == 'w')
	{
		close(fds[0]);
		return (fds[1]);
	}
	return -1;
}