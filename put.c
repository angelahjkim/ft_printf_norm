/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:26:00 by angkim            #+#    #+#             */
/*   Updated: 2019/09/06 21:49:05 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset_struct(t_format *f)
{
	MOD = 0;
	FLAGS = 0;
	LEN = 0;
	WIDTH = -1;
	f->p = 0;
	PREC = -1;
	P_ZERO = 0;
	P_SPACE = 0;
	f->spec = 'n';
	f->arg_num = -1;
}

void	put_padding(t_format *f)
{
	if ((FLAGS & F_PLUS || FLAGS & F_SPACE) && f->spec != '%')
	{
		WIDTH--;
		if (!(f->spec == 'u'))
			COUNT++;
	}
	if (PREC > LEN)
		WIDTH -= (PREC - LEN);
	while (LEN < WIDTH && PREC < WIDTH)
	{
		if (FLAGS & F_ZERO)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		WIDTH--;
		COUNT++;
	}
	while (WIDTH < 0 && PREC > LEN)
	{
		write(1, "0", 1);
		PREC--;
		COUNT++;
	}
	if (FLAGS & F_ZERO)
		FLAGS -= F_ZERO;
}

void	put_prefix(t_format *f)
{
	if ((f->spec == 'd' || f->spec == 'i') && f->d_arg > 0)
	{
		if ((FLAGS & F_PLUS || FLAGS & F_SPACE) && !f->p)
		{
			WIDTH--;
			COUNT++;
		}
		if (FLAGS & F_PLUS)
		{
			ft_putchar('+');
			FLAGS -= F_PLUS;
		}
		else if (FLAGS & F_SPACE)
		{
			ft_putchar(' ');
			FLAGS -= F_SPACE;
		}
	}
	else if (f->spec == 'o' || f->spec == 'x' || f->spec == 'X')
		put_prefix_ox_xx(f);
}

void	put_prefix_ox_xx(t_format *f)
{
	while (PREC > LEN)
	{
		ft_putnbr(0);
		COUNT++;
		PREC--;
		WIDTH--;
	}
	if (FLAGS & F_HASH)
	{
		ft_putchar('0');
		if (f->spec == 'x')
			ft_putchar('x');
		else if (f->spec == 'X')
			ft_putchar('X');
		(f->spec == 'o') ? (COUNT++) : (COUNT += 2);
		FLAGS -= F_HASH;
	}
}
