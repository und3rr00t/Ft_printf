/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oused-da <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:51:55 by oused-da          #+#    #+#             */
/*   Updated: 2025/12/08 16:53:32 by oused-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
		ft_putchar(s[i++]);
	return (i);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
		len += ft_putnbr_unsigned(n / 10);
	len += ft_putchar((n % 10) + 48);
	return (len);
}

int	ft_putnbr(int n)
{
	long int	nb;
	int			len;

	len = 0;
	nb = n;
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
		len += ft_putnbr(nb / 10);
	len += ft_putchar((nb % 10) + 48);
	return (len);
}
