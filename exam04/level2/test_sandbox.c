/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sandbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:05:41 by ahouass           #+#    #+#             */
/*   Updated: 2025/06/06 13:47:40 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>


void	handle_sig(int sig)
{
	(void)sig;	
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int					status;
	int					pid;
	struct sigaction	sa;

	sa.sa_flags = 0;
	sa.sa_handler = handle_sig;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGALRM, &sa, NULL);

	alarm(timeout);

	pid = fork();
	if (pid == -1)
		return -1;
	if (pid == 0)
	{
		f();
		exit(0);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		if(errno == EINTR)
		{
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
			if(verbose)
				printf("Bad function: timed out after <timeout> seconds\n", timeout);
			return 0;
		}
		return -1;
	}
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
		{
			if(verbose)
				printf("Nice function!\n");
			return 1;
		}
		else
		{
			if(verbose)
				printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
			return 0;
		}
	}
	if (WIFSIGNALED(status))
	{
		if(verbose)
			printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
		return 0;
	}
	return -1;
}