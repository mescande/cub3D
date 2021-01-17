/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:25:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 15:07:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		c3d_show(t_gnrl *data)
{
	int	err;

	printf("COUCOU%d\n", __LINE__);
	err = 0;
	if (data->player.rot)
		err = rotate(data);
	if (data->player.mov)
	{
		data->player.pos[X] += data->player.mov * 0.1 * data->player.dir[X];
		data->player.pos[Y] += data->player.mov * 0.1 * data->player.dir[Y];
		err = 1;
	}
	if (err)
	{
		if ((err = calcul_img(data)))
			return (err);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img,
				0, 0);
	}
	return (0);
}

int		c3d_key(int key, t_gnrl *data, int press)
{
	if (key == 65307)//escape
	{
		if (!press && data->quit)
			mlx_loop_end(data->mlx.mlx);
		else
			data->quit = 1;
	}
	if (key == 65364)//down
		data->player.mov = -press;
	if (key == 65362)//up
		data->player.mov = press;
	if (key == 65363)//right
		data->player.rot = -press;
	if (key == 65361)//left
		data->player.rot = press;
	(void)data;
	return (0);
}

int		key_release(int key, t_gnrl *data)
{
	printf("COUCOU%d\n", __LINE__);
	return (c3d_key(key, data, 0));
}

int		key_press(int key, t_gnrl *data)
{
	printf("COUCOU%d\n", __LINE__);
	return (c3d_key(key, data, 1));
}

int		c3d_loop(t_gnrl *data)
{
	int err;

//	mlx_key_hook(data->mlx.win, c3d_key, data);
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->file.res[X],
			data->file.res[Y]);
	data->mlx.line = (unsigned int *)mlx_get_data_addr(data->mlx.img, &err,
			&data->mlx.size, &err);
	data->mlx.size = data->mlx.size / 4;
	if ((err = calcul_img(data)))
		return (err);
	mlx_hook(data->mlx.mlx, 02, (1L<<0), key_press, data);//keypress
	mlx_hook(data->mlx.mlx, 03, (1L<<1), key_release, data);//keyrelease
/*	mlx_hook(data->mlx.mlx, , , , data);
	mlx_hook(data->mlx.mlx, , , , data);
	mlx_hook(data->mlx.mlx, , , , data);
	mlx_hook(data->mlx.mlx, , , , data);
*/	mlx_loop_hook(data->mlx.mlx, c3d_show, data);
	mlx_loop(data->mlx.mlx);
	printf("COUCOU%d\n", __LINE__);
	return (0);
}
