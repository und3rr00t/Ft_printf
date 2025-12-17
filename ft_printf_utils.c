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

void	ft_putchar(char c, int *len)
{
	if (*len == -1)
		return ;
	if (write(1, &c, 1) == -1)
		*len = -1;
	else
		*len += 1;
}

void	ft_putstr(char *s, int *len)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)", len));
	while (s[i])
		ft_putchar(s[i++], len);
}

void	ft_putnbr_unsigned(unsigned int n, int *len)
{
	if (n > 9)
		ft_putnbr_unsigned(n / 10, len);
	ft_putchar((n % 10) + 48, len);
}

void	ft_putnbr(int n, int *len)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-', len);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10, len);
	ft_putchar((nb % 10) + 48, len);
}
