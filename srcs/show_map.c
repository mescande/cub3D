/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:42:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 20:19:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_map_color(char val)
{
	int color;

	if (is_wall(val))
		color = 0x500050;
	else if (val == 1)
		color = 0x8080a0;
	else if (val == 2)
		color = 0xa8080;
	else if (val == 'H')
		color = 0x1010ff;
	else if (val == 3)
		color = 0xa0a0a0;
	else
		color = 0x505050;
	return (color);
}

static int	put_squares(int *coord, int *val, t_gnrl *data)
{
	int		color;
	int		i;
	int		j;

	color = set_map_color(data->player.map[coord[X] + val[X]][coord[Y] + val[Y]]);
	i = -1;
	while (++i < 9 && data->player.map[coord[X] + val[X]][coord[Y] + val[Y]] != ' ')
	{
		j = -1;
		while (++j < 9)
			data->mlx.line[(val[X] * 9 + i) * data->mlx.size + val[Y] * 9 + j] = color;
	}
	return (0);
}

int			show_map(t_gnrl *data)
{
	int max[2];
	int	val[2];
	int	start[2];

	start[X] = (int)data->player.pos[X] - 10;
	if (start[X] < 0)
		start[X] = 0;
	max[X] = start[X] + 20;
	if (max[X] > data->file.map.height)
	{
		max[X] = data->file.map.height;
		if (data->file.map.height > 20)
			start[X] = max[X] - 20;
	}
	val[X] = 0;
	while (val[X] + start[X] < max[X] && data->player.show_map)
	{
		start[Y] = (int)data->player.pos[Y] - 10;
		if (start[Y] < 1)
			start[Y] = 1;
		max[Y] = start[Y] + 20;
		if (max[Y] > data->file.map.length)
		{
			max[Y] = data->file.map.length;
			if (data->file.map.length > 20)
				start[Y] = max[Y] - 20;
		}
		val[Y] = -1;
		while (++val[Y] + start[Y] < max[Y] + 1)
			put_squares(start, val, data);
		val[X]++;
	}
	return (0);
}
