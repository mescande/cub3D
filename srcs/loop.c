/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:25:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/30 15:05:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		c3d_show(t_gnrl *data)
{
	int	err;

	err = 0;
	if (data->player.rot[X] || data->player.rot[Y])
		err += rotate(data);
	if (data->player.mov[X] || data->player.mov[Y])
		err += movement(data);
	if (data->player.tran[X] || data->player.tran[Y])
		err += translate(data);
	if (err || data->player.reload)
	{
		if ((err || data->player.reload == 1) && (err = calcul_img(data)))
			return (err);
		data->player.reload = 0;
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img,
				0, 0);
	}
	return (0);
}

int		c3d_key(int key, t_gnrl *data, int press)
{
	if (key == ESC)
	{
		if (!press && data->quit)
			mlx_loop_end(data->mlx.mlx);
		else
			data->quit = 1;
	}
	if (key == DOWN || key == S_KEY)
		data->player.mov[X] += (press == 1 ? 1 : -1);
	if (key == UP || key == W_KEY)
		data->player.mov[Y] += (press == 1 ? 1 : -1);
	if (key == RIGHT || key == E_KEY)
		data->player.rot[X] += (press == 1 ? 1 : -1);
	if (key == LEFT || key == Q_KEY)
		data->player.rot[Y] += (press == 1 ? 1 : -1);
	if (key == A_KEY)
		data->player.tran[X] += (press == 1 ? 1 : -1);
	if (key == D_KEY)
		data->player.tran[Y] += (press == 1 ? 1 : -1);
	if (key == TAB && press)
	{
		data->player.reload = 1;
		data->player.show_map = (data->player.show_map + 1) % 2;
	}
	return (0);
}

int		c3d_loop(t_gnrl *data)
{
	int err;

	data->mlx.img = mlx_new_image(data->mlx.mlx, data->file.res[X],
			data->file.res[Y]);
	data->mlx.line = (unsigned int *)mlx_get_data_addr(data->mlx.img, &err,
			&data->mlx.size, &err);
	data->mlx.size = data->mlx.size / 4;
	mlx_do_key_autorepeatoff(data->mlx.mlx);
	mlx_hook(data->mlx.win, 02, (1L << 0), key_press, data);
	mlx_hook(data->mlx.win, 03, (1L << 1), key_release, data);
	mlx_hook(data->mlx.win, 33, (1L << 17), mlx_loop_end, data->mlx.mlx);
	mlx_hook(data->mlx.win, 10, (1L << 21), focus_out, data);
	mlx_hook(data->mlx.win, 9, (1L << 21), focus_in, data);
	mlx_hook(data->mlx.win, 12, (1L << 15), expose, data);
	mlx_loop_hook(data->mlx.mlx, c3d_show, data);
	if ((err = calcul_img(data)))
		return (err);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img,
				0, 0);
	mlx_loop(data->mlx.mlx);
	mlx_do_key_autorepeaton(data->mlx.mlx);
	mlx_do_sync(data->mlx.mlx);
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	return (0);
}
