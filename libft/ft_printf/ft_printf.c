/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:43:50 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/30 19:05:49 by gcozigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	prntf_putchar(char c)
{
	write(2, &c, 1);
	return (1);
}

int	for_p(va_list *args)
{
	unsigned long	fff;

	fff = va_arg(*args, unsigned long);
	if (!fff)
		return (write(2, "(nil)", 5));
	else
		return (prntf_putstr("0x") + prntf_putnbr_base_p(fff, BASE_XX));
}

int	prntf_sort(char c, va_list *args)
{
	int	count;

	count = 0;
	if (c == 'c')
		return (prntf_putchar(va_arg(*args, int)));
	else if (c == 's')
		return (prntf_putstr(va_arg(*args, char *)));
	else if (c == 'd' || c == 'i')
		return (prntf_putnbr(va_arg(*args, int), &count));
	else if (c == 'u')
		return (prntf_putnbr_u(va_arg(*args, unsigned int)));
	else if (c == 'x')
		return (prntf_putnbr_base(va_arg(*args, unsigned int), BASE_XX));
	else if (c == 'X')
		return (prntf_putnbr_base(va_arg(*args, unsigned int), BASE_X));
	else if (c == 'p')
		return (for_p(&*args));
	else
		return (prntf_putchar('%'));
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		index;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	index = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			index += prntf_sort(format[++i], &args);
		}
		else
			index += prntf_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (index);
}
