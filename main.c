/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:38:11 by acastelb          #+#    #+#             */
/*   Updated: 2020/11/30 14:33:26 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

static int	get_size(long int n)
{
	int			i;

	i = 1;
	if (n < 0)
		n += 4294967296;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*create_str(char *str, long int n, int len)
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
	char		*str;
	int			len;

	if (n < 0)
		n += 4294967296;
	len = get_size(n);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str = create_str(str, n, len);
	return (str);
}

char	*ft_convert_hex(long int nb, char *base)
{
	int size;
	int is_neg;
	long int n;
	char *str;

	is_neg = 0;
	n = nb;
	size = 1;
	if (n < 0)
	{
		size += 1;
		n *= -1;
	}
	while (n >= 16)
	{
		n /= 16;
		size += 1;
	}
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

char	*ft_get_params_str(char c, va_list ap)
{
	char *str;

	if (c == 'c')
	{
		c = (va_arg(ap,int));
		str = strndup(&c, 1);
	}
	else if (c == 'p')
		str = ft_convert_hex(va_arg(ap, unsigned long long), "0123456789abcdef");
	else if (c == 's')
		str = strdup(va_arg(ap,char *));
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

int		ft_conversion(char *s, va_list ap, t_list **to_print)
{
	int		i;
	char	*str;
	char c;
	t_list	*new;

	str = NULL;
	i = -1;
	while (s[++i] && ft_strchr("cspdiuxX%", s[i]) == 0)
		;
	if (ft_strchr("cspdiuxX%", s[i]))
	{
		str = ft_get_params_str(s[i], ap);
		/*
		if (s[i] == 'c')
		{
			c = (va_arg(ap,int));
			str = strndup(&c, 1);
		}
		else if (s[i] == 'p')
			str = ft_convert_hex(va_arg(ap, unsigned long long), "0123456789abcdef");
		else if (s[i] == 's')
			str = strdup(va_arg(ap,char *));
		else if (s[i] == 'd' || s[i] == 'i')
			str = ft_itoa(va_arg(ap, int));
		else if (s[i] == 'u')
			str = ft_utoa(va_arg(ap, unsigned int));
		else if (s[i] == 'x')
			str = ft_convert_hex(va_arg(ap, unsigned int), "0123456789abcdef");
		else if (s[i] == 'X')
			str = ft_convert_hex(va_arg(ap, unsigned int), "0123456789ABCDEF");
		else if (s[i] == '%')
			str = strdup("%");
		*/
		if (str == NULL)
			return (-1);
		new = ft_lstnew(str);
		ft_lstadd_back(to_print, new);
	}
	return (i);
}

int		ft_print_all(t_list *to_print)
{
	int len;

	len = 0;
	while (to_print)
	{
		if (to_print->content)
			ft_putstr_fd((char *)to_print->content, 1);
		len += ft_strlen((char *)to_print->content);
		to_print = to_print->next;
	}
	return (len);
}

int		ft_printf(const char *s, ...)
{
	va_list		ap;
	t_list	*to_print;
	char		*tmp;
	int			i;
	int j;

	va_start(ap, s);
	i = 0;
	j = -1;
	while (s[++j])
		if (s[j] == '%')
		{
			tmp = strndup(s + i, j - i);
			ft_lstadd_back(&to_print, ft_lstnew((void *)tmp));
			i = j;
			if ((j = ft_conversion((char *)&s[i += 1], ap, &to_print)) == -1)
			{
				ft_lstclear(&to_print, free);
				return (-1);
			}
			i+= 1;
			j += i;
		}
	if (j > i)
	{
		tmp = strndup(s + i, j - i);
		ft_lstadd_back(&to_print, ft_lstnew((void *)tmp));
	}
	i = ft_print_all(to_print);
	ft_lstclear(&to_print, free);
	va_end(ap);
	return (i);
}


int main(int ac, char **av)
{
	int a = 200;
	int *p = &a;
	printf("Je m'appelles %s, mais on m'appelles %c, j'ai %d ans et mesure %x cm'", "Adrien", 'a', 20, 178);
}
