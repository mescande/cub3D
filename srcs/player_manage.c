/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:50:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/16 18:42:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		player_manage(t_gnrl *data)
{
	data->player.pos[X] = data->file.map.start[X];
	data->player.pos[Y] = data->file.map.start[Y];
	data->player.dir[X] = 1;
	data->player.dir[Y] = 0;
	data->player.plane[X] = 0;
	data->player.plane[Y] = atan(data->fov * M_PI_4 / 90);
	data->player.life = 100;
	return ;
//	return (0);
}
