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

#include "printf.h"
#include <stdio.h>

static	int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

static	int	ft_putstr(char	*str)
{
	int	i;
	int count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		count += ft_putchar(str[i]);
		i++;
	}
	return (count);
}
// static	int		countdigit(int nbr)
// {
// 	int count;

// 	count = 0;
// 	if (nbr == 0)
// 		return (1);
// 	if(nbr < 0)
// 		count++;
// 	while (nbr != 0)
// 	{
// 		nbr = nbr / 10;
// 		count++;
// 	}
// 	return (count);
// }

// static	void	ft_putnbr(int nbr)
// {
// 	long long n;
// 	n = nbr;
// 	if (n < 0)
// 	{
// 		ft_putchar('-');
// 		n = -n;
// 	}
// 	if (n  >= 10)
// 		ft_putnbr(n / 10 );
// 	ft_putchar(n % 10 + '0');
// }

static	int	ft_putnbr_base(long long nbr, int base, int uppercase)
{
	char *key;
	int count;

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
	char *key;
	int count;

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

// static	void	ft_puthexamin(int nbr)
// {
// 	unsigned long n;

// 	n = nbr;
// 	// if (nbr < 0)
// 	// {
// 	// 	// ft_putchar('-');
// 	// 	n = -nbr;
// 	// }
// 	if (n > 15)
// 		ft_puthexamin((n / 16));
// 	if ((n % 16 )>= 10 )
// 		ft_putchar(n % 16 + 97 - 10);
// 	else
// 		ft_putchar(n % 16 + '0');
// }
static	int	check_format(char format, va_list list, int count)
{

	
	if(format == '%')
				count += ft_putchar('%');
	else if (format == 'c')
				count += ft_putchar(va_arg(list, int));
	else if( format == 's')
			count += ft_putstr(va_arg(list, char *));
	else if( format == 'd' || format == 'i')
				count += ft_putnbr_base(va_arg(list, int), 10, 0);
	else if(format == 'u')
				count += ft_putnbr_base((unsigned int)va_arg(list, unsigned int), 10, 0);
	else if(format == 'x')
				count += ft_putnbr_base((unsigned int)va_arg(list, unsigned int), 16, 0);
	else if(format == 'X')
				count += ft_putnbr_base((unsigned int)va_arg(list, unsigned int), 16, 1);
	else if(format == 'p')
			{
				count += ft_putstr("0x");
				count += ft_putnbr_base_pointer((unsigned int)va_arg(list, unsigned long), 16, 0);
			}
	else
		count = 0;
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int i;
	va_list list;
	int count;

	va_start(list, format);
	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if(format[i] == '%')
		{
			i++;
			
			// if(format[i] == '%')
			// 	count += ft_putchar('%');
			// else if (format[i] == 'c')
			// 	count += ft_putchar(va_arg(list, int));
			// else if( format[i] == 's')
			// 	count += ft_putstr(va_arg(list, char *));
			// else if( format[i] == 'd' || format[i] == 'i')
			// 	count += ft_putnbr_base(va_arg(list, int), 10, 0);
			// else if(format[i] == 'u')
			// 	count += ft_putnbr_base((unsigned int)va_arg(list, unsigned int), 10, 0);
			// else if(format[i] == 'x')
			// 	count += ft_putnbr_base((unsigned int)va_arg(list, unsigned int), 16, 0);
			// else if(format[i] == 'X')
			// 	count += ft_putnbr_base((unsigned int)va_arg(list, unsigned int), 16, 1);
			// else if(format[i] == 'p')
			// {
			// 	count += ft_putstr("0x");
			// 	count += ft_putnbr_base((unsigned int)va_arg(list, unsigned long), 16, 0);
			// }
			count = check_format(format[i], list, count);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(list);
	return(count);
}

int main()
{
	// int a = ft_printf("%d ayoub ouahidi\n", 1000);
	// int p = printf("%d ayoub ouahidi\n",1000);
	// printf("ayoub's count : %d\nstring's count : %d\n", a, p);

	// some other test
	// int count = countdigit(n);
	// ft_putnbr(n);
	// ft_putchar('\n');
	int count = ft_printf("%s\n", "hello");
	printf("%d\n", count);

}
