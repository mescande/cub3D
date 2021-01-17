/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooky.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:12:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 20:19:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		rotate(t_gnrl *data)
{
	double	save;
	double	cv;
	double	sv;

	cv = cos(1. * data->player.rot * M_PI_4 / 45);
	sv = sin(1. * data->player.rot * M_PI_4 / 45);
	save = data->player.dir[X];
	data->player.dir[X] = data->player.dir[X] * cv - data->player.dir[Y] * sv;
	data->player.dir[Y] = data->player.dir[Y] * cv + save * sv;
/*	save = sqrt(pow(data->player.dir[X], 2) + pow(data->player.dir[Y], 2)); 
	data->player.dir[X] = data->player.dir[X] / save;
	data->player.dir[Y] = data->player.dir[Y] / save;
*/	save = data->player.plane[X];
	data->player.plane[X] = data->player.plane[X] * cv -
		data->player.plane[Y] * sv;
	data->player.plane[Y] = data->player.plane[Y] * cv + save * sv;
/*	save = sqrt(pow(data->player.dir[X], 2) + pow(data->player.dir[Y], 2)); 
	data->player.plane[X] = 3.5 * data->player.plane[X] / save;
	data->player.plane[Y] = 3.5 * data->player.plane[Y] / save;
*/	return (1);
}

int		movement(t_gnrl *data)
{
	int		ret;
	double	add;
	double	save;

	add = data->player.mov * 0.1 * data->player.dir[X];
	save = data->player.pos[X];
	if (data->file.map.map[(int)(add * 3 +
				data->player.pos[X])][(int)(data->player.pos[Y])] != '1')
	{
		data->player.pos[X] += add;
		ret = 1;
	}
	add = data->player.mov * 0.1 * data->player.dir[Y];
	if (data->file.map.map[(int)(save)][(int)(add * 3 +
				data->player.pos[Y])] != '1')
	{
		data->player.pos[Y] += add;
		ret = 1;
	}
	return (ret);
}
