/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:38:11 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/02 14:45:53 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

static int	get_size(long int n, int syst)
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

char		*ft_get_params_str(char c, va_list ap)
{
	char	*str;
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
		str = strdup(va_arg(ap, char *));
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

char		*ft_transform_str(char *src, t_infos *infos)
{
	char	*str;
	int		start;

	if (!(str = (char *)malloc(sizeof(char) * (infos->width + 1))))
		return (NULL);
	str[infos->width] = '\0';
	if (infos->_0_ && !infos->align && infos->precision < 0)
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

	if (ft_strchr("diuxX", c) && src[0] == '-' && infos->precision > ft_strlen(src + 1))
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

t_infos		*ft_infosnew(void)
{
	t_infos *new;

	if (!(new = (t_infos*)malloc(sizeof(t_infos))))
		return (NULL);
	new->_0_ = 0;
	new->width = -1;
	new->align = 0;
	new->precision = -1;
	return (new);
}

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
			(*infos)->_0_ = 1;
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

int			main(int ac, char **av)
{
	int		a;
	int		*p;
	char	*s;

	a = 200;
	p = &a;
	printf("|%030.20d|\n", -1110);
	ft_printf("|%030.20d|", -1110);
}
