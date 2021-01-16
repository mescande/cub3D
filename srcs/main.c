/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 17:17:16 by mescande          #+#    #+#             */
/*   Updated: 2021/01/16 19:32:54 by user42           ###   ########.fr       */
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
	if ((err = parsit(&(data.file), av[args_management(ac, av, &data)])))
		return (ft_freeemee(&data, err));
	player_manage(&data);
	if ((err = start_mlx(&data)))
		return (ft_freeemee(&data, err));
	printf("\n\
data.file.res[X] = %d\n\
     .....res[Y] = %d\n\
     .....map.height   = %d\n\
          ....length   = %d\n\
          ....start[X] = %d\n\
          ....start[Y] = %d\n\
     .....textures.name= %s\n\
          .........id  = %d\n\
     .....ceilling[1.2.3] [%d.%d.%d]\n\
     .....floor[1.2.3]    [%d.%d.%d]\n\
.....mlx.mlx = %p\n\
     ....win = %p\n\
     ....img = %p\n\
.....player.pos[X]  = %f\n\
     .......pos[Y]  = %f\n\
     .......dir[X]  = %f\n\
     .......dir[Y]  = %f\n\
     .......plane[X]= %f\n\
     .......plane[Y]= %f\n\
     .......posi[X] = %d\n\
     .......posi[Y] = %d\n\
     .......life    = %d\n\
.....fov = %f\n\
.....is_smart = %d\n\
", data.file.res[X], data.file.res[Y],
		 data.file.map.height, data.file.map.length, data.file.map.start[X],
		 data.file.map.start[Y], data.file.textures->name, data.file.textures->id,
		 data.file.ceiling[0], data.file.ceiling[1], data.file.ceiling[2],
		 data.file.floor[0], data.file.floor[1], data.file.floor[2],
		 data.mlx.mlx, data.mlx.win, data.mlx.img, data.player.pos[X],
		 data.player.pos[Y], data.player.dir[X], data.player.dir[Y],
		 data.player.plane[X], data.player.plane[Y], data.player.posi[X],
		 data.player.posi[Y], data.player.life, data.fov, data.is_smart);
	if ((err = c3d_loop(&data)))
		return (ft_freeemee(&data, err));
	return (ft_freeemee(&data, 0));
}
