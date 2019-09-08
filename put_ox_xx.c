/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ox_xx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:26:00 by angkim            #+#    #+#             */
/*   Updated: 2019/09/06 22:35:26 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_hex(char **format, t_format *f, va_list args)
{
	uint64_t tmp;

	get_mod_arg_ox_xx(f, args);
	if (f->ox_arg == 0 && f->w_val == -1)
		put_ox_zero(f);
	else
	{
		tmp = f->ox_arg;
		while (tmp / 16)
		{
			f->arg_len++;
			tmp /= 16;
		}
		f->arg_len++;
		f->count += f->arg_len;
		put_hex_flags(f);
	}
	(*format)++;
	reset_struct(f);
}

void	put_hex_flags(t_format *f)
{
	f->w_val -= (f->flags & F_HASH) ? 2 : 0;
	if (f->flags & F_MINUS)
	{
		put_prefix(f);
		(f->ox_arg != 0) ? ft_puthex_lower(f->ox_arg) : ft_putchar(' ');
		put_padding(f);
		f->flags -= F_MINUS;
	}
	else
	{
		if (f->flags & F_ZERO && f->flags & F_HASH)
		{
			put_prefix(f);
			put_padding(f);
		}
		else
		{
			put_padding(f);
			put_prefix(f);
		}
		if (f->spec == 'x')
			(f->ox_arg != 0) ? ft_puthex_lower(f->ox_arg) : ft_putchar(' ');
		else if (f->spec == 'X')
			(f->ox_arg != 0) ? ft_puthex_upper(f->ox_arg) : ft_putchar(' ');
	}
}

void	put_octal(char **format, t_format *f, va_list args)
{
	uint64_t tmp;

	get_mod_arg_ox_xx(f, args);
	if (f->ox_arg == 0 && f->w_val == -1)
		put_ox_zero(f);
	else
	{
		tmp = f->ox_arg;
		while (tmp / 8)
		{
			f->arg_len++;
			tmp /= 8;
		}
		f->arg_len++;
		f->count += f->arg_len;
		put_octal_flags(f);
	}
	(*format)++;
	reset_struct(f);
}

void	put_octal_flags(t_format *f)
{
	if (f->flags & F_HASH)
		f->w_val--;
	if (f->flags & F_MINUS)
	{
		put_prefix(f);
		(f->ox_arg != 0) ? ft_putoctal(f->ox_arg) : ft_putchar(' ');
		put_padding(f);
		f->flags -= F_MINUS;
	}
	else if (f->flags & F_ZERO && !(f->flags & F_HASH))
	{
		put_prefix(f);
		put_padding(f);
		(f->ox_arg != 0) ? ft_putoctal(f->ox_arg) : ft_putchar(' ');
	}
	else
	{
		put_padding(f);
		put_prefix(f);
		(f->ox_arg != 0) ? ft_putoctal(f->ox_arg) : ft_putchar(' ');
	}
}

void	put_ox_zero(t_format *f)
{
	if (FLAGS & F_HASH)
	{
		if (f->spec == 'x' || f->spec == 'X')
		{
			if (!f->p)
				write(1, "0", 1);
			else
				return ;
		}
		else if (f->spec == 'o')
		{
			if (f->p && (PREC == 0 || PREC == 1))
				write(1, "0", 1);
			else if (PREC == -1 && WIDTH == -1)
				write(1, "0", 1);
		}
	}
	else if (f->w_val == -1 && !(f->p))
		write(1, "0", 1);
	else if (f->p && f->p_val != -1)
		return ;
	COUNT++;
}
