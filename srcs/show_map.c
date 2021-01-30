/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:42:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/30 15:33:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_color(char val)
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

static int	put_squares(int x, int y, t_gnrl *data)
{
	int		color;
	int		i;
	int		j;

	color = set_color(data->player.map[x][y]);
	i = -1;
	y--;
	while (++i < 9 && data->player.map[x][y + 1] != ' ')
	{
		j = -1;
		while (++j < 9)
			data->mlx.line[(x * 9 + i) * data->mlx.size + (y * 9) + j] = color;
	}
	return (0);
}

int			show_map(t_gnrl *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->file.map.height && data->player.show_map)
	{
		y = 1;
		while (y < data->file.map.length + 1)
			put_squares(x, y++, data);
		x++;
	}
	return (0);
}
