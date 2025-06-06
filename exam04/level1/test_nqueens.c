/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_nqueens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:48:35 by ahouass           #+#    #+#             */
/*   Updated: 2025/06/04 20:00:54 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

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

void	ft_solve(int *positions, int col, int size)
{
	int i = 0;
	if(col == size)
	{
		while(i < size)
		{
			printf("%d", positions[i]);
			if(i < size - 1)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	while(i < size)
	{
		if(is_safe(positions, col, i))
		{
			positions[col] = i;
			ft_solve(positions, col + 1, size);
		}
		i++;
	}
}

int main(int ac, char **av)
{
	int		n;
	if (ac != 2)
		return 1;
	n = atoi(av[1]);
	int	*positions = malloc(n * 4);
	if (!positions)
		return 1;
	ft_solve(positions, 0, n);
	free(positions);
	return 0;
}