/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:01:55 by bcosters          #+#    #+#             */
/*   Updated: 2021/07/29 11:06:39 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static char	ul_to_char(t_ul toconvert)
{
	char	c;

	c = toconvert % 10;
	c += 48;
	return (c);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	while (str++)
		ft_putchar_fd(*str, fd);
}

void	ft_putnbr_ulong_fd(t_ul n, int fd)
{
	if (n != ULONG_MAX)
	{
		if (n < 10)
		{
			ft_putchar_fd(ul_to_char(n), fd);
		}
		if (n >= 10)
		{
			ft_putnbr_ulong_fd(n / 10, fd);
			ft_putchar_fd(ul_to_char(n), fd);
		}
	}
	else
	{
		ft_putstr_fd("18446744073709551615", fd);
	}
}
