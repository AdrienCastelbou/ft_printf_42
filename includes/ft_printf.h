/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:31:14 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/09 14:50:25 by acastelb         ###   ########.fr       */
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
	int			zero;
	int			width;
	int			align;
	int			precision;
	int			conversion;
	int			printed;
}				t_infos;

int				ft_printf(const char *s, ...);
int				ft_conversion(char *s, va_list ap, int printed);
t_infos			*ft_infosnew(int printed);
char			*ft_strcpy(char *dest, char *src);
int				get_size(long int n, int syst);
char			*create_str(char *str, long int n, int len);
char			*ft_utoa(long int n);
char			*ft_convert_hex(long int nb, char *base);
int				ft_get_conversion(char c, va_list ap, t_infos *infos);
void			ft_get_width_infos(char *s, t_infos **infos, va_list ap);
void			ft_get_precision_infos(char *s, t_infos **infos, va_list ap);
char			*ft_transform_neg(char *src, t_infos *infos);
char			*ft_transform_str(char *src, t_infos *infos);
char			*ft_precise_nb(char *str, t_infos *infos);
char			*ft_precise_neg(char *src, t_infos *infos);
int				ft_print_char(char c, t_infos *infos);
int				ft_print_pointer(unsigned long long nb, t_infos *infos);
int				ft_print_params(char *str, t_infos *infos);
int				ft_print_str(char *str, t_infos *infos);
void			ft_free_all(char *str, t_infos *infos);
#endif
