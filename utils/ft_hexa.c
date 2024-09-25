/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:01:55 by alion             #+#    #+#             */
/*   Updated: 2024/01/11 15:29:28 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_hex(unsigned int nbr, const char str)
{
	if (nbr >= 16)
	{
		ft_put_hex(nbr / 16, str);
		ft_put_hex(nbr % 16, str);
	}
	else
	{
		if (nbr < 10)
			ft_putchar_fd((nbr + '0'), 1);
		else
		{
			if (str == 'x')
				ft_putchar_fd((nbr - 10 + 'a'), 1);
			if (str == 'X')
				ft_putchar_fd((nbr - 10 + 'A'), 1);
		}
	}
}

int	ft_hexa(unsigned int nbr, const char str)
{
	int	length;

	length = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(nbr, str);
	while (nbr != 0)
	{
		length++;
		nbr = nbr / 16;
	}
	return (length);
}
