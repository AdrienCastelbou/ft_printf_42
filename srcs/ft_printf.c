/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:38:11 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/08 14:49:46 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "../includes/ft_printf.h"

char		*ft_make_precise(char *str, t_infos *infos)
{
	if (infos->conversion == 's' && infos->precision < ft_strlen(str))
		str[infos->precision] = '\0';
	else if (ft_strchr("diuxX", infos->conversion))
		return (ft_precise_nb(str, infos));
	return (str);
}

char		*ft_strcpy(char *dest, char *src)
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

t_infos		*ft_infosnew(void)
{
	t_infos *new;

	if (!(new = (t_infos*)malloc(sizeof(t_infos))))
		return (NULL);
	new->zero = 0;
	new->width = 0;
	new->align = 0;
	new->precision = -1;
	return (new);
}

int			ft_print_char(char c, t_infos *infos)
{
	int		i;
	char	width;

	width = ' ';
	if (infos->zero)
		width = '0';
	i = -1;
	if (infos->align)
		write(1, &c, 1);
	while (++i < infos->width - 1)
		write(1, &width, 1);
	if (!infos->align)
		write(1, &c, 1);
	return (i + 1);
}

int			ft_conversion(char *s, va_list ap)
{
	t_infos *infos;

	infos = ft_infosnew();
	ft_get_width_infos(s, &infos, ap);
	ft_get_precision_infos(s, &infos, ap);
	if (infos->conversion == 0)
		return (0);
	return (ft_get_conversion(infos->conversion, ap, infos));
}

int			ft_printf(const char *s, ...)
{
	va_list		ap;
	int			i;
	int			count;

	count = 0;
	va_start(ap, s);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '%')
		{
			++i;
			count += ft_conversion((char *)&s[i], ap);
			while (s[i] && !ft_strchr("cspdiuxX%", s[i]))
				i++;
		}
		else
			count += write(1, &s[i], 1);
		if (!s[i])
			break ;
	}
	va_end(ap);
	return (count);
}
