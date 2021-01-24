/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:42:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 10:20:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	put_squares(int x, int y, t_gnrl *data)
{
	int	color;
	int	i;
	int j;
	char	val;

	val = data->player.map[x][y];
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
	i = -1;
	y--;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			if (data->player.map[x][y + 1] != ' ')
				data->mlx.line[(x * 10 + i) * data->mlx.size + (y * 10) + j] = color;
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
