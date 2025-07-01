/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:14:20 by ahouass           #+#    #+#             */
/*   Updated: 2025/07/01 18:04:17 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void    print_set(int *power_set, int powerset_size)
{
    int i = 0;
    while (i < powerset_size)
    {
        printf("%d", power_set[i]);
        if (i < powerset_size - 1)
            printf(" ");
        i++;
    }
    printf("\n");
}

void    ft_backtrack(int *set, int size, int target, int index, int *power_set, int powerset_size)
{
    int i;
    int sum;

    if (index == size)
    {
        i = 0;
        sum = 0;
        while (i < powerset_size)
        {
            sum += power_set[i];
            i++;
        }
        if (sum == target)
            print_set(power_set, powerset_size);
        return ;
    }
    power_set[powerset_size] = set[index];
    ft_backtrack(set, size, target, index + 1, power_set, powerset_size + 1);
    ft_backtrack(set, size, target, index + 1, power_set, powerset_size);
}

int main(int ac, char **av)
{
	int	*set;
	int	*power_set;
	int	size;
	int	target;
	int	i;
    
    if (ac < 3)
        return 1;
    size = ac - 2;
    target = atoi(av[1]);
    power_set = malloc(size * 4);
    if (!power_set)
        return 1;
    set = malloc(size * 4);
    if (!set)
        return 1;
    i = 0;
    while (i < size)
    {
        set[i] = atoi(av[i + 2]);
        i++;
    }
    ft_backtrack(set, size, target, 0, power_set, 0);
    free(set);
	free(power_set);
    return 0;
}