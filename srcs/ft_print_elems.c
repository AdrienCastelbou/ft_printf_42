/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_elems.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:56:19 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/08 14:59:03 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "../includes/ft_printf.h"

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

int			ft_print_pointer(unsigned long long nb, t_infos *infos)
{
	char *str;
	char *tmp;

	tmp = ft_convert_hex(nb, "0123456789abcdef");
	str = ft_strjoin("0x", tmp);
	free(tmp);
	return (ft_print_params(str, infos));
}

int			ft_print_params(char *str, t_infos *infos)
{
	int len;

	str = ft_make_precise(str, infos);
	if (infos->width > ft_strlen(str))
		str = ft_transform_str(str, infos);
	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	write(1, str, len);
	free(infos);
	free(str);
	return (len);
}

int			ft_print_str(char *str, t_infos *infos)
{
	int		i;
	int		len;
	char	c;

	c = ' ';
	i = -1;
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (infos->precision >= 0 && infos->precision < len)
		len = infos->precision;
	if (infos->align)
		write(1, str, len);
	if (infos->zero && !infos->align)
		c = '0';
	while (++i < infos->width - len)
		write(1, &c, 1);
	if (!infos->align)
		write(1, str, len);
	if (i < 0)
		i = 0;
	return (i + len);
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
		if (s[++i] >= '0' && s[i] <= '9')
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
	(*infos)->conversion = s[i] - 0;
}
