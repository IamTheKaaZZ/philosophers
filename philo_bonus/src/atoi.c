/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 13:05:11 by bcosters          #+#    #+#             */
/*   Updated: 2021/08/16 11:57:27 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

/*
**Checks is char c is a digit*
*/

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

/*
**	checks if c is any type of whitespace char
*/

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

/*
**Function to convert a string to a number, including negatives*
**only converts if first two chars are - and a digit or digits*
*/

int	ft_atoi(const char *numstr)
{
	int	i;
	int	res;
	int	sign;

	while (ft_isspace(*numstr))
		numstr++;
	i = 0;
	res = 0;
	sign = 1;
	if (*numstr == '-')
	{
		sign = -1;
		i++;
	}
	if (*numstr == '+')
		i++;
	while (*(numstr + i))
	{
		if (!ft_isdigit(numstr[i]))
			break ;
		res = res * 10 + numstr[i] - '0';
		i++;
	}
	return (res * sign);
}
