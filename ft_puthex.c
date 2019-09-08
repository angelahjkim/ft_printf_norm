/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:47:24 by angkim            #+#    #+#             */
/*   Updated: 2019/09/06 22:28:43 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex_lower(uint64_t n)
{
	char	*hex_digits;

	hex_digits = "0123456789abcdef";
	if (n / 16)
		ft_puthex_lower(n / 16);
	write(1, &hex_digits[n % 16], 1);
}

void	ft_puthex_upper(uint64_t n)
{
	char	*hex_digits;

	hex_digits = "0123456789ABCDEF";
	if (n / 16)
		ft_puthex_upper(n / 16);
	write(1, &hex_digits[n % 16], 1);
}
