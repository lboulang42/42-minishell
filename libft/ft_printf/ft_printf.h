/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:33:41 by gcozigon          #+#    #+#             */
/*   Updated: 2023/08/30 17:37:25 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define BASE_XX "0123456789abcdef"
# define BASE_X "0123456789ABCDEF"

int	prntf_putchar(char c);
int	prntf_putstr(char *str);
int	prntf_putnbr(int nbr, int *count);
int	prntf_sort(char c, va_list *args);
int	prntf_printf(const char *format, ...);
int	prntf_putnbr_u(unsigned int nbr);
int	prntf_putnbr_base(unsigned int nbr, char *base);
int	prntf_putnbr_base_p(unsigned long int nbr, char *base);

#endif
