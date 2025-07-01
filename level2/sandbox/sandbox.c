/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:43:04 by ahouass           #+#    #+#             */
/*   Updated: 2025/07/01 18:17:01 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

void	ft_hadle_alarm(int sig)
{
	(void)sig;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int					status;
	struct sigaction	sa;
	pid_t				pid;

	sa.sa_flags = 0;
	sa.sa_handler = ft_hadle_alarm;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);

	pid = fork();
	if(pid == -1)
		return -1;
	if(pid == 0)
	{
		f();
		exit(0);
	}
	alarm(timeout);
	if(waitpid(pid, &status, 0) == -1)
	{
		if(errno == EINTR)
		{
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
			if(verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return 0;
		}
		return -1;
	}
	if(WIFEXITED(status))
	{
		if(WEXITSTATUS(status) == 0)
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
	if(WIFSIGNALED(status))
	{
		if(verbose)
			printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
		return 0;
	}
	return -1;
}

// From here on , the code below is just for testing your function , do not do push it in the exam

void nice_function(void)
{
	// This function does nothing and exits normally (exit code 0)
	return;
}

void bad_function_exit_code(void)
{
	// This function exits with code 1 (failure)
	exit(42);
}

void bad_function_segfault(void)
{
	// This function causes a segmentation fault
	int *ptr = NULL;
	*ptr = 42;  // This will cause a segfault
}

void bad_function_timeout(void)
{
	// This function runs indefinitely
	while (1) {}
}

void bad_function_sleep(void)
{
	// This function sleeps for more than the timeout and gets killed by alarm handler
	sleep(2);  // Sleep for 5 seconds (assuming timeout is less than 5 seconds)
}

int main()
{
	int	result;

	printf("Test 1: Normal function (Nice)\n");
	result = sandbox(nice_function, 5, true);
	printf("Result: %d\n", result);  // Expected output: 1 ("Nice function!")

	printf("Test 2: Bad function (Exit code 1)\n");
	result = sandbox(bad_function_exit_code, 5, true);
	printf("Result: %d\n", result);  // Expected output: 0 ("Bad function: exited with code 1")

	printf("Test 3: Bad function (Segfault)\n");
	result = sandbox(bad_function_segfault, 5, true);
	printf("Result: %d\n", result);  // Expected output: 0 ("Bad function: Segmentation fault")

	printf("Test 4: Bad function (Timeout)\n");
	result = sandbox(bad_function_timeout, 2, true);  // Timeout after 2 seconds
	printf("Result: %d\n", result);  // Expected output: 0 ("Bad function: timed out after 2 seconds")
 
	printf("Test 5: Bad function (Killed by SIGKILL)\n");
	result = sandbox(bad_function_sleep, 2, true);  // Timeout after 2 seconds
	printf("Result: %d\n", result);  // Expected output: 0 ("Bad function: timed out after 2 seconds")

	return 0;
}
