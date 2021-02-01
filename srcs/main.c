/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 17:17:16 by mescande          #+#    #+#             */
/*   Updated: 2021/02/01 13:59:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int ac, char **av)
{
	t_gnrl	data;
	int		err;

	ft_bzero(&data, sizeof(t_gnrl));
	data.file.floor = -1;
	data.file.ceiling = -1;
	if (!(err = args_management(ac, av, &data)))
		return (0);
	if ((err = parsit(&(data.file), av[data.file.ac], &data)))
		return (ft_freeemee(&data, err));
	if ((err = player_manage(&data)))
		return (ft_freeemee(&data, err));
	if (data.save)
		return (ft_freeemee(&data, screen_it(&data)));
	if ((err = start_mlx(&data)))
		return (ft_freeemee(&data, err));
	if ((err = c3d_loop(&data)))
		return (ft_freeemee(&data, err));
	return (ft_freeemee(&data, 0));
}
