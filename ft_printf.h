/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:31:14 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/01 17:15:19 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
typedef struct	s_infos
{
	int			_0_;
	int			width;
	int			align;
	int			precision;
	char		conversion;
}				t_infos;

#endif
