/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:09:17 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/04 20:12:10 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "../includes/ft_printf.h"
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
		if (s[i] >= '1' && s[i] <= '9' && (*infos)->width == 0)
		{
			(*infos)->width = ft_atoi(s + i);
			i += get_size((*infos)->width, 10) - 1;
		}
		else if (s[i] == '*')
		{
			(*infos)->width = va_arg(ap, int);
			if ((*infos)->width < 0)
				(*infos)->align = 1;
		}
		else if (s[i] == '0' && (*infos)->align == 0)
			(*infos)->zero = 1;
		else if (s[i] == '-')
			(*infos)->align = 1;
	}
	if ((*infos)->width < 0)
		(*infos)->width *= -1;
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
	while (s[i] && ft_strchr("cspdiuxX%", s[i]) == 0)
		i++;
	if (ft_strchr("cspdiuxX%.", s[i]))
		(*infos)->conversion = s[i];
}

char		*ft_transform_neg(char *src, t_infos *infos)
{
	char	*dst;

	if (!(dst = (char *)malloc(sizeof(char) * (infos->width + 1))))
		return (NULL);
	dst[infos->width] = '\0';
	ft_memset(dst, '0', infos->width);
	ft_strcpy(dst + (infos->width - ft_strlen(src + 1)), src + 1);
	dst[0] = '-';
	free(src);
	return (dst);

}

char		*ft_transform_str(char *src, t_infos *infos)
{
	char	*dst;
	int		start;

	if (src[0] == '-' && ft_strlen(src) -1 < infos->width &&
			infos->zero && !infos->align && infos->precision < 0)
		return (ft_transform_neg(src, infos));
	if (!(dst = (char *)malloc(sizeof(char) * (infos->width + 1))))
		return (NULL);
	dst[infos->width] = '\0';
	if (infos->zero && !infos->align && infos->precision < 0)
		ft_memset(dst, '0', infos->width);
	else
		ft_memset(dst, ' ', infos->width);
	start = infos->width - ft_strlen(src);
	if (infos->align)
		ft_memcpy(dst, src, ft_strlen(src));
	else
		ft_strcpy(dst + start, src);
	free(src);
	return (dst);
}

char		*ft_precise_nb(char *str, t_infos *infos)
{
	char *dst;

	if (str[0] == '-' && ft_strlen(str) -1 < infos->precision)
		return (ft_precise_neg(str, infos));
	else if (str[0] == '0' && infos->precision == 0)
	{
		str[0] = '\0';
		return (str);
	}
	else if (ft_strlen(str) < infos->precision)
	{
		if (!(dst = (char *)malloc(sizeof(char) * (infos->precision + 1))))
				return (NULL);
		ft_memset(dst, '0', infos->precision);
		ft_strcpy(dst + (infos->precision - ft_strlen(str)), str);
		free(str);
		return (dst);
	}
	return (str);
}

char		*ft_precise_neg(char *src, t_infos *infos)
{
	char	*tmp;
	char	*dst;

	if (!(dst = (char *)malloc(sizeof(char) * (infos->precision + 1))))
		return (NULL);
	dst[infos->precision] = '\0';
	ft_memset(dst, '0', infos->precision);
	ft_strcpy(dst + (infos->precision - ft_strlen(src + 1)), src + 1);
	tmp = dst;
	dst = ft_strjoin("-", tmp);
	free(src);
	free(tmp);
	return (dst);
}
