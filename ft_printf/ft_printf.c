/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:37:03 by ypacileo          #+#    #+#             */
/*   Updated: 2024/07/27 16:50:22 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putchar(char character)
{
	return (write(1, &character, 1));
}

int	ft_format(char letter, va_list arg)
{
	int	size;

	size = 0;
	if (letter == 'c')
		size += ft_putchar(va_arg(arg, int));
	else if (letter == 's')
		size += ft_putstr(va_arg(arg, char *));
	else if (letter == 'i' || letter == 'd')
		size += ft_print_number(va_arg(arg, int));
	else if (letter == 'u')
		size += ft_print_unsigned(va_arg(arg, unsigned));
	else if (letter == 'X')
		size += ft_number_hex(va_arg(arg, unsigned int), BASE_HEX_MAYUS);
	else if (letter == 'x')
		size += ft_number_hex(va_arg(arg, unsigned int), BASE_HEX_MINUS);
	else if (letter == 'p')
		size += ft_checkpointer(va_arg(arg, unsigned long), BASE_HEX_MINUS);
	else if (letter == '%')
		size += ft_putchar('%');
	return (size);
}

int	ft_printf(char const *str, ...)
{
	va_list	arg;
	int		size;

	va_start(arg, *str);
	size = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			size += ft_format(*str, arg);
		}
		else
			size += ft_putchar(*str);
		str++;
	}
	va_end(arg);
	return (size);
}
