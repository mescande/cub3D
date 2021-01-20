/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooky.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:12:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/20 14:07:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		rotate(t_gnrl *data)
{
	double	save;
	double	cv;
	double	sv;
	int		rot;

	rot = (data->player.rot[X] && data->player.rot[Y] ? 0 : 1);
	rot = rot * (data->player.rot[X] ? -1 : 1);
	cv = cos(2.5 * rot * M_PI_4 / 45);
	sv = sin(2.5 * rot * M_PI_4 / 45);
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

int		translate(t_gnrl *data)
{
	int		ret;
	double	add;
	double	save;
	int		tran;

	tran = (data->player.tran[X] && data->player.tran[Y] ? 0 : 1);
	tran = tran * (data->player.tran[X] ? -1 : 1);
	add = tran * 0.1 * data->player.plane[X];
	save = data->player.pos[X];
	if (data->file.map.map[(int)(add * 3 +
				data->player.pos[X])][(int)(data->player.pos[Y])] != '1')
	{
		data->player.pos[X] += add;
		ret = 1;
	}
	add = tran * 0.1 * data->player.plane[Y];
	if (data->file.map.map[(int)(save)][(int)(add * 3 +
				data->player.pos[Y])] != '1')
	{
		data->player.pos[Y] += add;
		ret = 1;
	}
	return (ret);
}

int		movement(t_gnrl *data)
{
	int		ret;
	double	add;
	double	save;
	int		mov;

	mov = (data->player.mov[X] && data->player.mov[Y] ? 0 : 1);
	mov = mov * (data->player.mov[X] ? -1 : 1);
	add = mov * 0.1 * data->player.dir[X];
	save = data->player.pos[X];
	if (data->file.map.map[(int)(add * 3 +
				data->player.pos[X])][(int)(data->player.pos[Y])] != '1')
	{
		data->player.pos[X] += add;
		ret = 1;
	}
	add = mov * 0.1 * data->player.dir[Y];
	if (data->file.map.map[(int)(save)][(int)(add * 3 +
				data->player.pos[Y])] != '1')
	{
		data->player.pos[Y] += add;
		ret = 1;
	}
	return (ret);
}

int		focus_out(int key, t_gnrl *data)
{
	(void)key;
	data->player.mov[X] = 0;
	data->player.mov[Y] = 0;
	data->player.rot[X] = 0;
	data->player.rot[Y] = 0;
	data->player.tran[X] = 0;
	data->player.tran[Y] = 0;
	return (0);
}

int		focus_in(int key, t_gnrl *data)
{
	(void)key;
	data->player.reload = 1;
	return (0);
}
