/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:18:30 by ahouass           #+#    #+#             */
/*   Updated: 2025/06/04 19:42:03 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		balance = 0;

int		ft_balance(char *str)
{
	int i = 0;
	int unclosed = 0;
	int unopened = 0;
	while(str[i])
	{
		if (str[i] == '(')
			unclosed++;
		else if (str[i] == ')')
		{
			if(unclosed > 0)
				unclosed--;
			else
				unopened++;
		}
		i++;
	}
	return unopened + unclosed;
}

void	ft_backtracking(char *str, int changes, int pos)
{
	int		i;
	if(balance == changes && !ft_balance(str))
	{
		puts(str);
		return ;
	}
	i = pos;
	while(str[i])
	{
		if(str[i] == '(' || str[i] == ')')
		{
			char c = str[i];
			str[i] = ' ';
			ft_backtracking(str, changes + 1, pos + 1);
			str[i] = c;
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	balance = ft_balance(av[1]);
	ft_backtracking(av[1], 0, 0);
}