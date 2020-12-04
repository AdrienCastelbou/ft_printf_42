/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:12:44 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/04 17:34:50 by acastelb         ###   ########.fr       */
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

char	*ft_convert_str(va_list ap)
{
	va_list	aq;
	char	*str;

	va_copy(aq, ap);
	if (va_arg(aq, char *) == NULL)
		str = ft_strdup("(null)");
	else
		str = strdup(va_arg(ap, char *));
	va_end(aq);
	return (str);
}

char		*ft_get_params_str(char c, va_list ap)
{
	char	*str = NULL;
	char	*tmp;

	if (c == 'c')
	{
		c = (va_arg(ap, int));
		str = strndup(&c, 1);
	}
	else if (c == 'p')
	{
		tmp = ft_convert_hex(va_arg(ap, unsigned long long),
				"0123456789abcdef");
		str = ft_strjoin("0x", tmp);
		free(tmp);
	}
	else if (c == 's')
		str = ft_convert_str(ap); 
	else if (c == 'd' || c == 'i')
		str = ft_itoa(va_arg(ap, int));
	else if (c == 'u')
		str = ft_utoa(va_arg(ap, unsigned int));
	else if (c == 'x')
		str = ft_convert_hex(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		str = ft_convert_hex(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		str = strdup("%");
	return (str);
}
