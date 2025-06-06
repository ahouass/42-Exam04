/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_permutaion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:27:57 by ahouass           #+#    #+#             */
/*   Updated: 2025/06/04 17:49:06 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
	{
		i++;
	}
	return i;
}

void	ft_sort(char *str)
{
	int i = 0;
	int j;
	while(str[i])
	{
		j = i + 1;
		while(str[j])
		{
			if (str[i] > str[j])
			{
				char tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_backtracking(char *str, char *perm, int *used, int len, int depth)
{
	int i = 0;
	if(depth == len)
	{
		perm[len] = '\0';
		puts(perm);
		return ;
	}
	while(str[i])
	{
		if(!used[i])
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
	if (ac != 2)
		return 1;
	ft_sort(av[1]);
	int len = ft_strlen(av[1]);
	char *perm = malloc(len + 1);
	int  *used = calloc(len , 4);
	ft_backtracking(av[1], perm, used, len, 0);
}