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

int	ft_formats(va_list *args, char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(*args, int));
	else if (format == 's')
		len += ft_putstr(va_arg(*args, char *));
	else if (format == 'p')
		len += ft_putptr(va_arg(*args, void *));
	else if (format == 'd' || format == 'i')
		len += ft_putnbr(va_arg(*args, int));
	else if (format == 'u')
		len += ft_putnbr_unsigned(va_arg(*args, unsigned int));
	else if (format == 'x')
		len += ft_puthex(va_arg(*args, unsigned int), 'x');
	else if (format == 'X')
		len += ft_puthex(va_arg(*args, unsigned int), 'X');
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	format_check(char c)
{
	char	*format;
	int		i;

	format = "cspdiuxX%";
	i = 0;
	while (format[i])
	{
		if (format[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] && format_check(s[i + 1]))
		{
			len += ft_formats(&args, s[i + 1]);
			i++;
		}
		else if (s[i] != '%')
			len += ft_putchar(s[i]);
		else if (s[i + 1])
			len += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (len);
}
