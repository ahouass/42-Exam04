/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nqueens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:44:38 by ahouass           #+#    #+#             */
/*   Updated: 2025/06/01 18:30:37 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		is_safe(int *positions, int col, int row)
{
	int i = 0;
	while(i < col)
	{
		if(positions[i] == row || abs(i - col) == abs(positions[i] - row))
            return 0;
		i++;
	}
	return 1;
}

void	ft_solve(int *positions, int col, int max)
{
	int i = 0;
	if(col == max)
	{
		while (i < max)
		{
			printf("%d", positions[i]);
			if(i < max - 1)
				printf(" ");
			i++;
		}
		printf("\n");
		return ;
	}
	
	while (i < max)
	{
		if(is_safe(positions, col, i))
		{
			positions[col] = i;
			ft_solve(positions, col + 1, max);
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int n = atoi(av[1]);
	int *positions = malloc(n * 4);
	if (!positions)
		return 1;
	ft_solve(positions, 0, n);
	free(positions);
	return 0;
}