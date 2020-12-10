/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:12:44 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/10 10:57:40 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "../includes/ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int			get_size(long int n, int syst)
{
	int			i;

	i = 1;
	if (n < 0)
		n *= -1;
	while (n >= syst)
	{
		n /= syst;
		i++;
	}
	return (i);
}

char		*create_str(char *str, long int n, int len)
{
	long int	nbr;

	str[len] = '\0';
	nbr = (n < 0) ? n * -1 : n;
	while (len--)
	{
		str[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char		*ft_utoa(long int n)
{
	char	*str;
	int		len;

	if (n < 0)
		n += 4294967296;
	len = get_size(n, 10);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str = create_str(str, n, len);
	return (str);
}

char		*ft_convert_hex(long int nb, char *base)
{
	int		size;
	char	*str;

	size = get_size(nb, 16);
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size] = '\0';
	while (size--)
	{
		str[size] = base[nb % 16];
		nb /= 16;
	}
	return (str);
}

int			ft_get_conversion(char c, va_list ap, t_infos *infos)
{
	if (c == 'c')
		return (ft_print_char(va_arg(ap, int), infos));
	else if (c == 's')
		return (ft_print_str(va_arg(ap, char *), infos));
	else if (c == 'p')
		return (ft_print_pointer(va_arg(ap, unsigned long long), infos));
	else if (c == 'd' || c == 'i')
		return (ft_print_params(ft_itoa(va_arg(ap, int)), infos));
	else if (c == 'u')
		return (ft_print_params(ft_utoa(va_arg(ap, unsigned int)), infos));
	else if (c == 'x')
		return (ft_print_params(ft_convert_hex(va_arg(ap, unsigned int),
						"0123456789abcdef"), infos));
	else if (c == 'X')
		return (ft_print_params(ft_convert_hex(va_arg(ap, unsigned int),
						"0123456789ABCDEF"), infos));
	else if (c == '%')
		return (ft_print_char('%', infos));
	else if (c == 'n')
		ft_set_print_value(va_arg(ap, int *), infos);
	return (0);
}
