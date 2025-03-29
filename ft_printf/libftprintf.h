/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:09:15 by ypacileo          #+#    #+#             */
/*   Updated: 2024/07/27 16:06:32 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>

# define BASE_HEX_MAYUS "0123456789ABCDEF"
# define BASE_HEX_MINUS "0123456789abcdef"

int	ft_putchar(char character);
int	ft_putstr(char *str);
int	ft_print_unsigned(unsigned int n);
int	ft_print_number(int n);
int	ft_format(char word, va_list arg);
int	ft_printf(char const *str, ...);
int	ft_number_hex(unsigned long number, char const *str);
int	ft_checkpointer(unsigned long pointer, char const *str);

#endif