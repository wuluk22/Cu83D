/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:19:16 by alion             #+#    #+#             */
/*   Updated: 2024/01/11 15:29:06 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_ptr(uintptr_t nbr)
{
	if (nbr >= 16)
	{
		ft_put_ptr(nbr / 16);
		ft_put_ptr(nbr % 16);
	}
	else
	{
		if (nbr <= 9)
			ft_putchar_fd((nbr + '0'), 1);
		else
			ft_putchar_fd((nbr - 10 + 'a'), 1);
	}
}

int	ft_ptr(unsigned long long str)
{
	int	length;

	length = 0;
	length += write(1, "0x", 2);
	if (str == 0)
		length += write(1, "0", 1);
	else
	{
		ft_put_ptr(str);
		while (str != 0)
		{
			length++;
			str /= 16;
		}
	}
	return (length);
}
