/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:33:33 by angkim            #+#    #+#             */
/*   Updated: 2019/09/06 22:48:17 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_format(char **format, t_format *f)
{
	while (**format == ' ' || **format == '+' || **format == '0'
		|| **format == '-' || **format == '#')
	{
		if (**format == '+')
			f->flags |= F_PLUS;
		if (**format == ' ')
			f->flags |= F_SPACE;
		if (**format == '-')
			f->flags |= F_MINUS;
		if (**format == '0')
			f->flags |= F_ZERO;
		if (**format == '#')
			f->flags |= F_HASH;
		(*format)++;
	}
	if ((f->flags & F_PLUS) && (f->flags & F_SPACE))
		f->flags -= F_SPACE;
	if ((f->flags & F_MINUS) && (f->flags & F_ZERO))
		f->flags -= F_ZERO;
	get_width(format, f);
}

void	get_width(char **format, t_format *f)
{
	if (ft_isdigit(**format))
	{
		f->w_val = ft_atoi(*format);
		(*format) += ft_digitcount(f->w_val);
	}
	get_precision(format, f);
}

void	get_precision(char **format, t_format *f)
{
	if (**format == '.')
	{
		f->p = 1;
		(*format)++;
		if (ft_isdigit(**format))
		{
			if (ft_isdigit(**format))
				f->p_val = ft_atoi(*format);
			(*format) += ft_digitcount(f->p_val);
		}
		else
			f->p_val = 1;
	}
	get_mod(format, f);
}

void	get_mod(char **format, t_format *f)
{
	if (**format == 'l' && *(*format + 1) != 'l')
		f->mod |= M_L;
	else if (**format == 'l' && *(*format + 1) == 'l')
	{
		f->mod |= M_LL;
		(*format)++;
	}
	else if (**format == 'h' && *(*format + 1) != 'h')
		f->mod |= M_H;
	else if (**format == 'h' && *(*format + 1) == 'h')
	{
		f->mod |= M_HH;
		(*format)++;
	}
	else if (**format == 'L')
		f->mod |= M_LD;
	if (f->mod > 0)
		(*format)++;
	f->spec = **format;
	check_percent(format, f);
}

void	check_percent(char **format, t_format *f)
{
	if (**format == '%')
	{
		f->arg_len = 1;
		if (f->flags & F_MINUS)
		{
			ft_putchar('%');
			put_padding(f);
			f->flags -= F_MINUS;
		}
		else
		{
			put_padding(f);
			ft_putchar('%');
		}
		f->arg_num = 10;
		f->count++;
		(*format)++;
	}
	else
		f->arg_num = -1;
}
