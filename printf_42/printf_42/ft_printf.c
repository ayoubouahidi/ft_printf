/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayouahid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:50:30 by ayouahid          #+#    #+#             */
/*   Updated: 2024/11/29 13:50:32 by ayouahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static	int	ft_putstr(char	*str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (str == NULL)
		return (write (1, "(null)", 6));
	while (str[i] != '\0')
	{
		count += ft_putchar(str[i]);
		i++;
	}
	return (count);
}

static	int	ft_putnbr_base(long long nbr, int base, int uppercase)
{
	char	*key;
	int		count;

	count = 0;
	if (uppercase)
		key = "0123456789ABCDEF";
	if (!uppercase)
		key = "0123456789abcdef";
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= base)
		count += ft_putnbr_base(nbr / base, base, uppercase);
	count += write(1, &key[nbr % base], 1);
	return (count);
}

static	int	ft_putnbr_base_pointer(unsigned long nbr, int base, int uppercase)
{
	char	*key;
	int		count;

	count = 0;
	if (nbr == 0)
		return (ft_putstr("(nil)"));
	count += ft_putstr("0x");
	if (uppercase)
		key = "0123456789ABCDEF";
	if (!uppercase)
		key = "0123456789abcdef";
	if (nbr >= (unsigned long)base)
		count += ft_putnbr_base(nbr / base, base, uppercase);
	count += write(1, &key[nbr % base], 1);
	return (count);
}

static	int	check_format(char format, va_list list, int count)
{
	if (format == '%')
		count += ft_putchar('%');
	else if (format == 'c')
		count += ft_putchar(va_arg(list, int));
	else if (format == 's')
		count += ft_putstr(va_arg(list, char *));
	else if (format == 'd' || format == 'i')
		count += ft_putnbr_base(va_arg(list, int), 10, 0);
	else if (format == 'u')
		count += ft_putnbr_base((unsigned int)va_arg(list, unsigned int), \
		10, 0);
	else if (format == 'x')
		count += ft_putnbr_base((unsigned int)va_arg(list, unsigned int), \
		16, 0);
	else if (format == 'X')
		count += ft_putnbr_base((unsigned int)va_arg(list, unsigned int), \
		16, 1);
	else if (format == 'p')
		count += ft_putnbr_base_pointer((unsigned long)va_arg(list, \
		unsigned long), 16, 0);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	list;
	int		count;

	if (format == NULL)
		return (-1);
	va_start(list, format);
	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
				return (-1);
			count = check_format(format[i], list, count);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(list);
	return (count);
}
