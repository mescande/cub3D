/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:50:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 02:01:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		map_cpy(char **map, t_map src)
{
	int	i;

	i = -1;
	while (++i < src.height)
		map[i] = ft_strcpy(map[i], src.map[i]);
}

static int	player_map(t_gnrl *data)
{
	int i;

	i = -1;
	if (!(data->player.map = (char **)malloc(sizeof(char *) *
					data->file.map.height)))
		return (4);
	while (++i < data->file.map.height)
		data->player.map[i] = ft_strdup(data->file.map.map[i]);
	return (0);
}

static int	sprite_init(t_gnrl *data)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (++i < data->file.map.height)
	{
		j = 1;
		while (++j < data->file.map.length)
			if (data->file.map.map[i][j] == '2')
				n++;
	}
	if (!(data->sp = ft_memalloc(sizeof(t_sprite) * n)))
		return (4);
	return (0);
}

int			player_manage(t_gnrl *data)
{
	data->player.pos[X] = data->file.map.start[X] + 0.5;
	data->player.pos[Y] = data->file.map.start[Y] + 0.5;
	if (data->file.map.dir == 'N' || data->file.map.dir == 'S')
	{
		data->player.dir[X] = -1. * (data->file.map.dir == 'N' ? 1 : -1);
		data->player.plane[Y] = 1 * (data->file.map.dir == 'N' ? 1 : -1);
	}
	if (data->file.map.dir == 'E' || data->file.map.dir == 'W')
	{
		data->player.dir[Y] = 1. * (data->file.map.dir == 'E' ? 1 : -1);
		data->player.plane[X] = 1 * (data->file.map.dir == 'E' ? 1 : -1);
	}
	if (player_map(data) || !(data->player.dists =
				ft_memalloc(sizeof(double) * data->file.res[X]))
			|| sprite_init(data))
		return (4);
	return (0);
}
