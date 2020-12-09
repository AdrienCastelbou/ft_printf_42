/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:38:11 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/09 14:55:32 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "../includes/ft_printf.h"

void		ft_free_all(char *str, t_infos *infos)
{
	if (str)
		free(str);
	if (infos)
		free(infos);
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

t_infos		*ft_infosnew(int printed)
{
	t_infos *new;

	if (!(new = (t_infos*)malloc(sizeof(t_infos))))
		return (NULL);
	new->zero = 0;
	new->width = 0;
	new->align = 0;
	new->precision = -1;
	new->printed = printed;
	return (new);
}

int			ft_conversion(char *s, va_list ap, int printed)
{
	t_infos *infos;

	infos = ft_infosnew(printed);
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
			count += ft_conversion((char *)&s[i], ap, count);
			while (s[i] && !ft_strchr("ncspdiuxX%", s[i]))
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
