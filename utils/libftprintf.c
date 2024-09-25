/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alion <alion@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:18:00 by alion             #+#    #+#             */
/*   Updated: 2024/01/11 15:33:38 by alion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	change(va_list args, const char str)
{
	int	length;

	length = 0;
	if (str == 'c')
		length += (ft_printchar(va_arg(args, int )));
	else if (str == 's')
		length += (ft_printstr(va_arg(args, char *)));
	else if (str == 'p')
		length += (ft_ptr(va_arg(args, unsigned long long)));
	else if (str == 'd' || str == 'i')
		length += (ft_printnbr(va_arg(args, int)));
	else if (str == 'u')
		length += (ft_putnbr_pos(va_arg(args, unsigned int)));
	else if (str == 'x' || str == 'X')
		length += (ft_hexa(va_arg(args, unsigned int), str));
	else if (str == '%')
		length += ft_percent();
	return (length);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		length;

	length = 0;
	va_start(args, str);
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			length += change(args, (*(str + 1)));
			str++;
		}
		else if (*str != '%')
			length += ft_printchar(*str);
		str++;
	}
	va_end(args);
	return (length);
}
