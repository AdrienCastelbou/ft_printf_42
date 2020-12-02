/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:31:14 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/02 15:28:27 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_infos
{
	int			_0_;
	int			width;
	int			align;
	int			precision;
	char		conversion;
}				t_infos;

int				ft_printf(const char *s, ...);
int				ft_conversion(char *s, va_list ap);
void			ft_get_precision_infos(char *s, t_infos **infos, va_list ap);
void			ft_get_width_infos(char *s, t_infos **infos, va_list ap);
t_infos			*ft_infosnew(void);
char			*ft_precise_str(char *src, char c, t_infos *infos);
char			*ft_precise_neg(char *src, t_infos *infos);
char			*ft_transform_str(char *src, t_infos *infos);
char			*ft_strcpy(char *dest, char *src);
char			*ft_get_params_str(char c, va_list ap);
char			*ft_convert_hex(long int nb, char *base);
char			*ft_utoa(long int n);
char			*create_str(char *str, long int n, int len);
int				get_size(long int n, int syst);
#endif
