/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:42:42 by ypacileo          #+#    #+#             */
/*   Updated: 2024/07/27 16:48:03 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putstr(char *str)
{
	int	size;

	size = 0;
	if (str == NULL)
		size = write(1, "(null)", 6);
	else
		while (*str)
			size += write(1, str++, 1);
	return (size);
}

int	ft_print_unsigned(unsigned int number)
{
	int	size;

	size = 0;
	if (number / 10 != 0)
		size += ft_print_unsigned(number / 10);
	size += ft_putchar((number % 10) + '0');
	return (size);
}

int	ft_print_number(int number)
{
	int	size;

	size = 0;
	if (number == 0)
		return (ft_putchar('0'));
	if (number == -2147483648)
		return (ft_putstr("-2147483648"));
	if (number < 0)
	{
		size = ft_putchar('-');
		number = -number;
	}
	if (number > 0)
		size += ft_print_unsigned(number);
	return (size);
}

int	ft_number_hex(unsigned long number, char const *str)
{
	int	size;
	int	index;

	size = 0;
	index = 0;
	if (number < 16)
	{
		index = number % 16;
		size += ft_putchar(str[index]);
	}
	else
	{
		size += ft_number_hex(number / 16, str);
		index = number % 16;
		size += ft_putchar(str[index]);
	}
	return (size);
}

int	ft_checkpointer(unsigned long pointer, char const *str)
{
	int	size;

	size = 0;
	if (!pointer)
		return (ft_putstr("(nil)"));
	else
	{
		size += ft_putstr("0x");
		size += ft_number_hex(pointer, str);
	}
	return (size);
}
