/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:38:11 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/01 10:02:35 by acastelb         ###   ########.fr       */
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
	char	*str;
	char	*tmp;

	if (c == 'c')
	{
		c = (va_arg(ap,int));
		str = strndup(&c, 1);
	}
	else if (c == 'p')
	{
		tmp = ft_convert_hex(va_arg(ap, unsigned long long), "0123456789abcdef");
		str = ft_strjoin("0x", tmp);
		free(tmp);
	}
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

char	*ft_strcpy(char *dest, char *src)
{
	size_t i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_transform_str(char	*src, char c, int width)
{
	char	*str;
	int		start;

	if (!(str = (char *)malloc(sizeof(char) * (width + 1))))
		return (NULL);
	str[width] = '\0';
	if (c == '0')
		ft_memset(str, '0', width);
	else
		ft_memset(str, ' ', width);
	start = width - ft_strlen(src);
	if (c == '-')
		ft_memcpy(str, src, ft_strlen(src));
	else
		ft_strcpy(str + start, src);
	free(src);
	return (str);
}

int		ft_conversion(char *s, va_list ap, t_list *to_print)
{
	int		i;
	int		width;
	int		w_indicator;
	char	*str;
	t_list	*new;

	str = NULL;
	i = -1;
	width = -1;
	w_indicator = 0;
	while (s[++i] && ft_strchr("cspdiuxX%", s[i]) == 0)
	{
		if (s[i] >= '1' && s[i] <= '9' && width == -1)
		{
			width = ft_atoi(s + i);
			i += get_size(width) - 1;
		}
		else if (s[i] == '*')
			width = va_arg(ap, int);
		else if ((s[i] == '0' && s[w_indicator] != '-') || s[i] == '-')
			w_indicator = i;
	}
	if (ft_strchr("cspdiuxX%", s[i]))
	{
		str = ft_get_params_str(s[i], ap);
		if (width > ft_strlen(str))
			str = ft_transform_str(str, s[w_indicator], width);
		if (str == NULL)
			return (-1);
		new = ft_lstnew(str);
		ft_lstadd_back(&to_print, new);
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
	t_list	*to_print = NULL;
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
			if ((j = ft_conversion((char *)&s[i += 1], ap, to_print)) == -1)
			{
				ft_lstclear(&to_print, free);
				return (-1);
			}
			i += j + 1;
			j = i - 1;
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
	printf("|%p|\n", p);
	ft_printf("|%p|", p);
}
