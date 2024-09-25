/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:11:53 by alion             #+#    #+#             */
/*   Updated: 2024/01/11 15:28:56 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_pos(unsigned int n)
{
	char	*nbr;
	int		length;

	length = ft_nbrlen(n);
	nbr = (char *)malloc(sizeof(char) * length);
	if (!nbr)
		return (0);
	while (n != 0)
	{
		nbr[length - 1] = n % 10 + '0';
		n /= 10;
		length--;
	}
	return (nbr);
}

int	ft_putnbr_pos(unsigned int n)
{
	char	*nbr;
	int		final;

	if (n == 0)
		final = write(1, "0", 1);
	else
	{
		nbr = ft_pos(n);
		final = ft_printstr(nbr);
		free (nbr);
	}
	return (final);
}
