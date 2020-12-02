/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:09:17 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/02 15:30:29 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

void		ft_get_width_infos(char *s, t_infos **infos, va_list ap)
{
	int i;

	i = -1;
	while (s[++i] && ft_strchr("cspdiuxX%.", s[i]) == 0)
	{
		if (s[i] >= '1' && s[i] <= '9' && (*infos)->width == -1)
		{
			(*infos)->width = ft_atoi(s + i);
			i += get_size((*infos)->width, 10) - 1;
		}
		else if (s[i] == '*')
			(*infos)->width = va_arg(ap, int);
		else if (s[i] == '0' && (*infos)->align == 0)
			(*infos)->zero = 1;
		else if (s[i] == '-')
			(*infos)->align = 1;
	}
}

void		ft_get_precision_infos(char *s, t_infos **infos, va_list ap)
{
	int i;

	i = -1;
	while (s[++i] && ft_strchr("cspdiuxX%.", s[i]) == 0)
		;
	if (s[i] == '.')
	{
		(*infos)->precision = 0;
		if (s[++i] >= '1' && s[i] <= '9')
		{
			(*infos)->precision = ft_atoi(s + i);
			i += get_size((*infos)->precision, 10) - 1;
		}
		else if (s[i] == '*')
		{
			(*infos)->precision = va_arg(ap, int);
			i++;
		}
	}
}

char		*ft_precise_neg(char *src, t_infos *infos)
{
	char	*tmp;
	char	*dst;

	tmp = ft_substr(src, 1, ft_strlen(src + 1));
	if (!(dst = (char *)malloc(sizeof(char) * (infos->precision + 1))))
		return (NULL);
	ft_memset(dst, '0', infos->precision);
	ft_strcpy(dst + (infos->precision - ft_strlen(tmp)), tmp);
	free(tmp);
	tmp = dst;
	dst = ft_strjoin("-", tmp);
	free(tmp);
	return (dst);
}

char		*ft_precise_str(char *src, char c, t_infos *infos)
{
	char	*dst;

	if (ft_strchr("diuxX", c) && src[0] == '-' &&
			infos->precision > ft_strlen(src + 1))
		return (ft_precise_neg(src, infos));
	if ((c == 's' && infos->precision < ft_strlen(src)) ||
			(ft_strchr("diuxX", c) && infos->precision > ft_strlen(src)))
	{
		if (!(dst = (char *)malloc(sizeof(char) * (infos->precision + 1))))
			return (NULL);
	}
	else
		return (src);
	dst[infos->precision] = '\0';
	if (c == 's')
		strncpy(dst, src, infos->precision);
	else
	{
		ft_memset(dst, '0', infos->precision);
		ft_strcpy(dst + (infos->precision - ft_strlen(src)), src);
	}
	free(src);
	return (dst);
}

char		*ft_transform_str(char *src, t_infos *infos)
{
	char	*str;
	int		start;

	if (!(str = (char *)malloc(sizeof(char) * (infos->width + 1))))
		return (NULL);
	str[infos->width] = '\0';
	if (infos->zero && !infos->align && infos->precision < 0)
		ft_memset(str, '0', infos->width);
	else
		ft_memset(str, ' ', infos->width);
	start = infos->width - ft_strlen(src);
	if (infos->align)
		ft_memcpy(str, src, ft_strlen(src));
	else
		ft_strcpy(str + start, src);
	free(src);
	return (str);
}
