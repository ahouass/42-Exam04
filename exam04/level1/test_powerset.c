/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_powerset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:49:45 by ahouass           #+#    #+#             */
/*   Updated: 2025/06/04 18:26:55 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	ft_print_set(int *powerset, int powerset_size)
{
	int i = 0;
	while(i < powerset_size)
	{
		printf("%d", powerset[i]);
		if (i < powerset_size - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	ft_backtrack(int *set, int target, int size, int index, int *powerset, int powerset_size)
{
	int i = 0;
	int sum = 0;
	if(index == size)
	{
		while(i < powerset_size)
		{
			sum += powerset[i];
			i++;
		}
		if(sum == target)
			ft_print_set(powerset, powerset_size);
		return ;
	}
	powerset[powerset_size] = set[index];
	ft_backtrack(set, target, size, index + 1, powerset, powerset_size + 1);
	ft_backtrack(set, target, size, index + 1, powerset, powerset_size);
}

int main(int ac, char **av)
{
	int	*set;
	int	*powerset;
	int	size;
	int target;
	
	if (ac < 3)
		return 1;
	target = atoi(av[1]);
	size = ac - 2;
	set = malloc(size * 4);
	if (!set)
		return 1;
	powerset = malloc(size * 4);
	if (!powerset)
		return 1;
	int i = 0;
	while(i < size)
	{
		set[i] = atoi(av[i + 2]);
		i++;
	}
	ft_backtrack(set, target, size, 0, powerset, 0);
	return 0;
}