/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:38:11 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/02 15:29:29 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

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
	new->width = -1;
	new->align = 0;
	new->precision = -1;
	return (new);
}

int			ft_conversion(char *s, va_list ap)
{
	int		i;
	char	*str;
	char	*tmp;
	t_infos *infos;

	infos = ft_infosnew();
	i = -1;
	ft_get_width_infos(s, &infos, ap);
	ft_get_precision_infos(s, &infos, ap);
	while (s[++i] && ft_strchr("cspdiuxX%", s[i]) == 0)
		;
	if (ft_strchr("cspdiuxX%", s[i]))
	{
		str = ft_get_params_str(s[i], ap);
		str = ft_precise_str(str, s[i], infos);
		if (infos->width > ft_strlen(str))
			str = ft_transform_str(str, infos);
		if (str == NULL)
			return (-1);
		write(1, str, ft_strlen(str));
		return (ft_strlen(str));
	}
	return (-1);
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
