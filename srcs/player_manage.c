/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:50:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 13:06:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		player_manage(t_gnrl *data)
{
	data->player.pos[X] = data->file.map.start[X] + 0.5;
	data->player.pos[Y] = data->file.map.start[Y] + 0.5;
	if (data->file.map.dir == 'N')
	{
		data->player.dir[X] = -1.;
		data->player.plane[Y] = 3.5;
	}
	if (data->file.map.dir == 'S')
	{
		data->player.dir[X] = 1.;
		data->player.plane[Y] = -3.5;
	}
	if (data->file.map.dir == 'E')
	{
		data->player.dir[Y] = 1.;
		data->player.plane[X] = -3.5;
	}
	if (data->file.map.dir == 'W')
	{
		data->player.dir[Y] = -1.;
		data->player.plane[X] = 3.5;
	}
//	data->player.plane[X] =  atan(data->fov * M_PI_4 / 90.);
//	data->player.plane[Y] =  -atan(data->fov * M_PI_4 / 90.);
	data->player.life = 100;
	return ;
//	return (0);
}
