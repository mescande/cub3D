/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 17:17:16 by mescande          #+#    #+#             */
/*   Updated: 2021/01/15 20:53:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int ac, char **av)
{
	t_gnrl	data;
	int		err;

	if (ac <= 1 || ac > 3)
		return (ft_puterror(6));
	ft_bzero(&data, sizeof(t_gnrl));
	if ((err = parsit(&(data.file), av[args_management(ac, av)])))
		return (ft_freeemee(&data, err));
	if ((err = start_mlx(&data)))
		return (ft_freeemee(&data, err));
/*	if ((err = mrt_loop(data)))
		return (ft_freeemee(&data, err, window));
*/	return (ft_freeemee(&data, 0));
}
