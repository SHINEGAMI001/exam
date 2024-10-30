/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachhab <hlachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 06:56:28 by hlachhab          #+#    #+#             */
/*   Updated: 2024/10/29 07:37:50 by hlachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_putstr(char *str, int *count)
{
	int	i;

	i = 0;
	if (!str)
	{
		str = "(null)";
	}
	while (str[i])
	{
		ft_putchar(str[i], count);
		i++;
	}
}

void	ft_putnbr(int nbr, int *count)
{
	char	c;

	if (nbr == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar('-', count);
		nbr *= -1;
	}
	if (nbr > 9)
		ft_putnbr(nbr / 10, count);
	c = (nbr % 10) + '0';
	ft_putchar(c, count);
}

void	ft_puthexa(unsigned int nbr, int *count)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr > 15)
		ft_puthexa(nbr / 16, count);
	ft_putchar(base[nbr % 16], count);
}
#include <stdio.h>

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, str);
	if (write(1, 0, 0) == -1)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			if (str[i] == '%')
				ft_putchar(str[i], &count);
			else if (str[i] == 's')
				ft_putstr(va_arg(ap, char *), &count);
			else if (str[i] == 'd')
				ft_putnbr(va_arg(ap, int), &count);
			else if (str[i] == 'x')
				ft_puthexa(va_arg(ap, unsigned int), &count);
			else
				ft_putchar(str[i], &count);
		}
		else
			ft_putchar(str[i], &count);
		i++;
	}
	va_end(ap);
	printf("count : %d\n", count);
	return (count);
}

int	main()
{
	ft_printf("\tTest 1 : %%s | %s\n", "g", "cc");
	printf("ocount : %d\n", printf("\tTest 2 : %s | %s\n", "", "cc"));
}