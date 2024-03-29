/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angkim <angkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:48:48 by angkim            #+#    #+#             */
/*   Updated: 2019/08/13 14:30:26 by angkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Writes n zeroed bytes to the string s. If n is zero, nothing is done.
*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_cpy;

	s_cpy = (unsigned char *)s;
	while (n--)
	{
		*s_cpy = 0;
		s_cpy++;
	}
}
