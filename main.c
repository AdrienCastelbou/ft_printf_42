/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:38:11 by acastelb          #+#    #+#             */
/*   Updated: 2020/11/27 18:32:46 by acastelb         ###   ########.fr       */
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
		if (s[i] == 'c')
		{
			c = (va_arg(ap,int));
			str = strndup(&c, 1);
		}
		else if (s[i] == 's')
			str = strdup(va_arg(ap,char *));
		else if (s[i] == 'd' || s[i] == 'i')
			str = ft_itoa(va_arg(ap, int));
		else if (s[i] == 'u')
			str = ft_utoa(va_arg(ap, unsigned int));
		new = ft_lstnew(str);
		ft_lstadd_back(to_print, new);
	}
	return (1);
}

void	ft_print_all(t_list *to_print)
{
	while (to_print)
	{
		if (to_print->content)
			ft_putstr_fd((char *)to_print->content, 1);
		to_print = to_print->next;
	}
}

int		ft_printf(const char *s, ...)
{
	va_list		ap;
	t_list	*to_print;
	char		*tmp;
	int			i;

	va_start(ap, s);
	i = -1;
	while (s[++i])
		if (s[i] == '%')
		{
			tmp = strndup(s, i);
			to_print = ft_lstnew((void *)tmp);
			ft_conversion((char *)&s[i + 1], ap, &to_print);
		}
	ft_print_all(to_print);
	ft_lstclear(&to_print, free);
	va_end(ap);
	return (1);
}


int main(int ac, char **av)
{
	ft_printf("hello %u", atoi(av[1]));
	printf("hello %u", atoi(av[1]));
}
