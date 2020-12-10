/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_precision_infos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:47:25 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/10 10:29:45 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "../includes/ft_printf.h"

void		ft_get_precision_infos(char *s, t_infos **infos, va_list ap)
{
	int i;

	i = -1;
	while (s[++i] && ft_strchr("ncspdiuxX%.", s[i]) == 0)
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
	while (s[i] && ft_strchr("ncspdiuxX%", s[i]) == 0)
		i++;
	(*infos)->conversion = s[i] - 0;
}

void		ft_set_print_value(int *pointer, t_infos *infos)
{
	if (pointer)
		*pointer = infos->printed;
	free(infos);
}
