/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oused-da <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:54:01 by oused-da          #+#    #+#             */
/*   Updated: 2025/12/08 16:55:13 by oused-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(unsigned long n, char format, int *len)
{
	char	*base;

	if (format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		ft_puthex(n / 16, format, len);
	ft_putchar(base[n % 16], len);
}

void	ft_putptr(void *ptr, int *len)
{
	unsigned long	address;

	if (!ptr)
	{
		ft_putstr("(nil)", len);
		return ;
	}
	address = (unsigned long)ptr;
	ft_putstr("0x", len);
	ft_puthex(address, 'x', len);
}
