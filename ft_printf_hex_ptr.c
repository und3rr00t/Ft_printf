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

int	ft_puthex(unsigned long n, char format)
{
	char	*base;
	int		len;

	len = 0;
	if (format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		len += ft_puthex(n / 16, format);
	len += ft_putchar(base[n % 16]);
	return (len);
}

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	int				len;

	len = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	address = (unsigned long)ptr;
	len += ft_putstr("0x");
	len += ft_puthex(address, 'x');
	return (len);
}
