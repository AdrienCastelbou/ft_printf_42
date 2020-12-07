/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:57:34 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/07 14:52:27 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/libft/libft.h"
#include "./includes/ft_printf.h"

int main()
{
int  ret;

//ret = printf("%14c", 0);
//printf("\nreturn value = %d\n", ret);
ret = ft_printf("%14c", 0);
printf("\nreturn value = %d\n", ret);
/*
ft_printf(" --- Return : %d\n", ft_printf("%3s, %8s, %---2s, %.*s, %.0s, %.1s, %.2s, %.4s, %.8s", NULL, NULL, NULL, -2, NULL, NULL, NULL, NULL, NULL, NULL));
printf(" --- Return : %d\n", printf("%3s, %8s, %---2s, %.*s, %.0s, %.1s, %.2s, %.4s, %.8s", NULL, NULL, NULL, -2, NULL, NULL, NULL, NULL, NULL, NULL));*/
}
