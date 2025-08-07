/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akiiski <akiiski@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:56:33 by akiiski           #+#    #+#             */
/*   Updated: 2024/11/19 11:33:40 by akiiski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	checknext(char type, va_list args)
{
	if (type == 's')
		return (ft_putstr_fd(va_arg(args, const char *), 1));
	else if (type == 'd' || type == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (type == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (type == 'u')
		return (ft_unbr_fd(va_arg(args, unsigned int), 1));
	else if (type == '%')
		return (ft_putchar_fd('%', 1));
	else if (type == 'X' || type == 'x')
		return (ft_hexnbr(va_arg(args, unsigned int), 1, type));
	else if (type == 'p')
		return (ft_pointer(va_arg(args, void *), 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			len += checknext(format[i + 1], args);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
