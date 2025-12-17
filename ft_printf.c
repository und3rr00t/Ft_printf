/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oused-da <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:48:39 by oused-da          #+#    #+#             */
/*   Updated: 2025/12/08 16:49:08 by oused-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_formats(va_list *args, char format, int *len)
{
	if (format == 'c')
		ft_putchar(va_arg(*args, int), len);
	else if (format == 's')
		ft_putstr(va_arg(*args, char *), len);
	else if (format == 'p')
		ft_putptr(va_arg(*args, void *), len);
	else if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(*args, int), len);
	else if (format == 'u')
		ft_putnbr_unsigned(va_arg(*args, unsigned int), len);
	else if (format == 'x')
		ft_puthex(va_arg(*args, unsigned int), 'x', len);
	else if (format == 'X')
		ft_puthex(va_arg(*args, unsigned int), 'X', len);
	else if (format == '%')
		ft_putchar('%', len);
	else
	{
		ft_putchar('%', len);
		ft_putchar(format, len);
	}
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		len;

	if (!s)
		return (-1);
	i = 0;
	len = 0;
	va_start(args, s);
	while (s[i])
	{
		if (len == -1)
			break ;
		if (s[i] == '%' && s[i + 1])
			ft_formats(&args, s[++i], &len);
		else if (s[i] != '%')
			ft_putchar(s[i], &len);
		i++;
	}
	va_end(args);
	return (len);
}
