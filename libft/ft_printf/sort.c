/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:30:09 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/30 17:38:43 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	prntf_putstr(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (write(2, "(null)", 6));
	while (*str)
		index += prntf_putchar(*str++);
	return (index);
}

int	prntf_putnbr(int nbr, int *count)
{
	if (nbr == -2147483648)
		return (write(2, "-2147483648", 11));
	if (nbr < 0)
	{
		*count += prntf_putchar(45);
		nbr = nbr * -1;
	}
	if (nbr > 9)
		prntf_putnbr(nbr / 10, count);
	*count += prntf_putchar((nbr % 10) + 48);
	return (*count);
}

int	prntf_putnbr_u(unsigned int nbr)
{
	static int	index;

	index = 0;
	if (nbr < 10)
		index += prntf_putchar(nbr + 48);
	else
	{
		prntf_putnbr_u(nbr / 10);
		index += prntf_putchar((nbr % 10) + 48);
	}
	return (index);
}

int	prntf_putnbr_base(unsigned int nbr, char *base)
{
	static int	index;

	index = 0;
	if (nbr >= 16)
		prntf_putnbr_base((nbr / 16), base);
	index += prntf_putchar(base[nbr % 16]);
	return (index);
}

int	prntf_putnbr_base_p(unsigned long int nbr, char *base)
{
	static int	index;

	index = 0;
	if (nbr >= 16)
		prntf_putnbr_base_p((nbr / 16), base);
	index += prntf_putchar(base[nbr % 16]);
	return (index);
}
