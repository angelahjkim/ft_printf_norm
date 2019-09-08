/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 12:18:32 by angkim            #+#    #+#             */
/*   Updated: 2019/09/07 17:02:19 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_modf(t_format *f, va_list args, long double *n, char **s)
{
	uint64_t	whole;
	int			neg;

	neg = 0;
	if (MOD == 'L')
		*n = (long double)va_arg(args, long double);
	else
		*n = (long double)va_arg(args, double);
	if (*n < 0)
	{
		*n *= -1;
		neg = 1;
		COUNT++;
	}
	whole = ((uint64_t)*n);
	*n = *n - ((uint64_t)*n);
	if (!f->p)
		PREC = 6;
	LEN = ft_digitcount(whole) + 1 + PREC;
	*s = ft_memalloc(sizeof(char) * LEN + 1);
	*s = ft_llutoa(whole);
	return (neg ? 1 : 0);
}

void	put_float(char **format, t_format *f, va_list args)
{
	char		*f_str;
	long double	f_arg;
	int			neg;

	f_str = NULL;
	neg = get_modf(f, args, &f_arg, &f_str);
	P_SPACE = WIDTH - LEN;
	put_pad_float(f, &f_str, &f_arg);
	(neg) ? ft_putchar('-') : 0;
	ft_putstr(f_str);
	COUNT += ft_strlen(f_str);
	free(f_str);
	(*format)++;
	reset_struct(f);
}

void	put_pad_float(t_format *f, char **f_str, long double *f_arg)
{
	int		i;
	double	cast;

	i = 0;
	cast = 0;
	if (!(FLAGS & F_MINUS))
	{
		while (P_SPACE-- > 0)
			write(1, " ", 1);
		COUNT++;
	}
	i += ft_digitcount(ft_atoi(*f_str));
	if ((f->p && !(PREC == -1 || PREC == 0)) || (!f->p))
		*f_str[i++] = '.';
	while (PREC-- > 0)
	{
		*f_arg *= 10;
		cast = (*f_arg > 0) ? 0.5 : -0.5;
		*f_str[i++] = ((uint64_t)(*f_arg + cast) % 10) + 48;
		*f_arg = *f_arg - (uint64_t)*f_arg;
	}
	*f_str[i] = '\0';
}
