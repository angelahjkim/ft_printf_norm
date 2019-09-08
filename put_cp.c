/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:26:00 by angkim            #+#    #+#             */
/*   Updated: 2019/09/06 21:44:13 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_ordinary(char **format, t_format *f)
{
	ft_putchar(**format);
	f->count++;
	(*format)++;
}

void	put_char(char **format, t_format *f, va_list args)
{
	int c;

	c = va_arg(args, int);
	if (f->w_val > 1)
	{
		if (f->flags & F_MINUS)
			ft_putchar(c);
		while (f->w_val > 1)
		{
			ft_putchar(' ');
			f->w_val--;
			f->count++;
		}
		if (!(f->flags & F_MINUS))
			ft_putchar(c);
	}
	else
		ft_putchar(c);
	f->w_val = 0;
	f->count++;
	(*format)++;
	reset_struct(f);
}

void	put_address(char **format, t_format *f, va_list args)
{
	long	add_arg;

	add_arg = va_arg(args, long);
	ft_hexlen(add_arg, &LEN);
	LEN += 2;
	if (WIDTH < LEN)
	{
		ft_putstr("0x");
		ft_puthex_long(add_arg);
	}
	else if (WIDTH > LEN)
	{
		if (!(FLAGS & F_MINUS))
			put_pad_add(f, &add_arg);
		else if (FLAGS & F_MINUS)
			put_pad_add_minus(f, &add_arg);
	}
	COUNT += LEN;
	(*format)++;
	reset_struct(f);
}

void	put_pad_add(t_format *f, long *add_arg)
{
	while (WIDTH-- > LEN)
	{
		write(1, " ", 1);
		COUNT++;
	}
	ft_putstr("0x");
	ft_puthex_long(*add_arg);
}

void	put_pad_add_minus(t_format *f, long *add_arg)
{
	ft_putstr("0x");
	ft_puthex_long(*add_arg);
	while (WIDTH-- > LEN)
	{
		write(1, " ", 1);
		COUNT++;
	}
}
