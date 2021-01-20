/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:50:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 23:59:26 by user42           ###   ########.fr       */
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

int			player_manage(t_gnrl *data)
{
	data->player.pos[X] = data->file.map.start[X] + 0.5;
	data->player.pos[Y] = data->file.map.start[Y] + 0.5;
	if (data->file.map.dir == 'N' || data->file.map.dir == 'S')
	{
		data->player.dir[X] = -1. * (data->file.map.dir == 'N' ? 1 : -1);
		data->player.plane[Y] = 0.75 * (data->file.map.dir == 'N' ? 1 : -1);
	}
	if (data->file.map.dir == 'E' || data->file.map.dir == 'W')
	{
		data->player.dir[Y] = 1. * (data->file.map.dir == 'E' ? 1 : -1);
		data->player.plane[X] = 0.75 * (data->file.map.dir == 'E' ? 1 : -1);
	}
	if (player_map(data))
		return (4);
	return (0);
}
