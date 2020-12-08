/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastelb <acastelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 13:57:34 by acastelb          #+#    #+#             */
/*   Updated: 2020/12/08 11:08:14 by acastelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/libft/libft.h"
#include "./includes/ft_printf.h"

int main()
{/*
	{1, 457, "c_nullterm_basic", c_nullterm_basic, c_nullterm_basic_bench, "{return test(\"%c\", '\0');}"},
	{1, 458, "c_nullterm_5w", c_nullterm_5w, c_nullterm_5w_bench, "{return test(\"%5c\", '\0');}"},
	{1, 459, "c_nullterm_5wlj", c_nullterm_5wlj, c_nullterm_5wlj_bench, "{return test(\"%-5c\", '\0');}"},*/
	printf("|%5c|\n", '\0');
	ft_printf("|%5c|\n", '\0');
}
