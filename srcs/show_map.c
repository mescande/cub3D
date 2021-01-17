/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:42:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 20:04:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	show_map(t_gnrl *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->file.map.height)
	{
		y = 1;
		while (y < data->file.map.length + 1)
			put_square(x, y++, data);
		x++;
	}
	return (0);
}

int put_square(int x, int y, t_gnrl *data)
{
	int	color;
	int	i;
	int j;
	char	val;

	val = data->player.map[x][y];
    if (val == '1')
        color = 0x500050;
    else if (val == '8')
        color = 0x000050;
    else if (val == '9')
        color = 0xff0000; 
	else
		color = 0x505050;
	i = -1;
	y--;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			data->mlx.line[(x * 10 + i) * data->mlx.size + (y * 10) + j] = color;
	}
	return (0);
}
