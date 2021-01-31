/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooky.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:12:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 19:13:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		focus_out(t_gnrl *data)
{
	data->player.mov[X] = 0;
	data->player.mov[Y] = 0;
	data->player.rot[X] = 0;
	data->player.rot[Y] = 0;
	data->player.tran[X] = 0;
	data->player.tran[Y] = 0;
	mlx_do_key_autorepeaton(data->mlx.mlx);
	return (0);
}

int		focus_in(t_gnrl *data)
{
	data->player.reload = 2;
	if (data->mlx.mlx)
		mlx_do_key_autorepeatoff(data->mlx.mlx);
	return (0);
}

int		key_release(int key, t_gnrl *data)
{
	int		res;

	res = c3d_key(key, data, 0);
	if (data->player.mov[X] < 0)
		data->player.mov[X] = 0;
	if (data->player.mov[Y] < 0)
		data->player.mov[Y] = 0;
	if (data->player.rot[X] < 0)
		data->player.rot[X] = 0;
	if (data->player.rot[Y] < 0)
		data->player.rot[Y] = 0;
	if (data->player.tran[X] < 0)
		data->player.tran[X] = 0;
	if (data->player.tran[Y] < 0)
		data->player.tran[Y] = 0;
	return (res);
}

int		key_press(int key, t_gnrl *data)
{
	return (c3d_key(key, data, 1));
}

int		expose(t_gnrl *data)
{
	data->player.reload = 2;
	return (0);
}
