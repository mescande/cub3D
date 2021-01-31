/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:03:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 12:34:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	hitbox(t_gnrl *data, double *add, int dir)
{
	double	pos[2];
	double	size;
	char	**map;

	pos[X] = data->player.pos[X];
	pos[Y] = data->player.pos[Y];
	size = 0.2;
	map = data->file.map.map;
	if (dir == X &&
		(is_stop(map[(int)(pos[X] + add[X] + size)][(int)(pos[Y] + size)])
		|| is_stop(map[(int)(pos[X] + add[X] + size)][(int)(pos[Y] - size)])
		|| is_stop(map[(int)(pos[X] + add[X] - size)][(int)(pos[Y] + size)])
		|| is_stop(map[(int)(pos[X] + add[X] - size)][(int)(pos[Y] - size)])))
		return (0);
	if (dir == Y &&
		(is_stop(map[(int)(pos[X] + size)][(int)(pos[Y] + add[Y] + size)])
		|| is_stop(map[(int)(pos[X] + size)][(int)(pos[Y] + add[Y] - size)])
		|| is_stop(map[(int)(pos[X] - size)][(int)(pos[Y] + add[Y] + size)])
		|| is_stop(map[(int)(pos[X] - size)][(int)(pos[Y] + add[Y] - size)])))
		return (0);
	return (1);
}

int			rotate(t_gnrl *data)
{
	double	save;
	double	cv;
	double	sv;
	int		rot;

	rot = (data->player.rot[X] && data->player.rot[Y] ? 0 : 1);
	rot = rot * (data->player.rot[X] ? -1 : 1);
	cv = cos(3 * rot * M_PI_4 / 45);
	sv = sin(3 * rot * M_PI_4 / 45);
	save = data->player.dir[X];
	data->player.dir[X] = data->player.dir[X] * cv - data->player.dir[Y] * sv;
	data->player.dir[Y] = data->player.dir[Y] * cv + save * sv;
	save = data->player.plane[X];
	data->player.plane[X] = data->player.plane[X] * cv -
		data->player.plane[Y] * sv;
	data->player.plane[Y] = data->player.plane[Y] * cv + save * sv;
	return (1);
}

int			translate(t_gnrl *data)
{
	int		ret;
	double	add[2];
	int		tran;

	tran = (data->player.tran[X] && data->player.tran[Y] ? 0 : 1);
	tran = tran * (data->player.tran[X] ? -1 : 1);
	add[X] = tran * 0.1 * data->player.plane[X];
	add[Y] = tran * 0.1 * data->player.plane[Y];
	if (hitbox(data, add, X))
	{
		data->player.pos[X] += add[X];
		ret = 1;
	}
	if (hitbox(data, add, Y))
	{
		data->player.pos[Y] += add[Y];
		ret = 1;
	}
	return (ret);
}

int			movement(t_gnrl *data)
{
	int		ret;
	double	add[2];
	int		mov;

	mov = (data->player.mov[X] && data->player.mov[Y] ? 0 : 1);
	mov = mov * (data->player.mov[X] ? -1 : 1);
	add[X] = mov * 0.1 * data->player.dir[X];
	add[Y] = mov * 0.1 * data->player.dir[Y];
	ret = 0;
	if (hitbox(data, add, X))
	{
		data->player.pos[X] += add[X];
		ret++;
	}
	if (hitbox(data, add, Y))
	{
		data->player.pos[Y] += add[Y];
		ret = 1;
	}
	return (ret);
}
