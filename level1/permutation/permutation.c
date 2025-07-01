/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:18:55 by ahouass           #+#    #+#             */
/*   Updated: 2025/05/31 18:11:27 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return i;
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_sort(char *str)
{
	int i = 0;
	int j;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] > str[j])
			{
				char tmp = str[j];
				str[j] = str[i];
				str[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_backtracking(char *str, char *perm, int *used, int len, int depth)
{
	int i = 0;
	
	if (depth == len)
	{
		perm[depth] = '\0';
		puts(perm);
		return ;
	}

	while (i < len)
	{
		if (!used[i])
		{
			used[i] = 1;
			perm[depth] = str[i];
			ft_backtracking(str, perm, used, len, depth + 1);
			used[i] = 0;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	int		len;
	char	*perm;
	int		*used;
	
	if (ac != 2)
		return 0;
	len = ft_strlen(av[1]);
	perm = malloc(len + 1);
	used = calloc(len + 1, 4);
	ft_sort(av[1]);
	ft_backtracking(av[1], perm, used, len, 0);
	free(perm);
	free(used);
	return 0;
}