/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:25:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/16 23:33:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		c3d_show(t_gnrl *data)
{
	int	err;

	err = 0;
	if (data->mlx.img)
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img,
				0, 0);
	else
	{
		data->mlx.img = mlx_new_image(data->mlx.mlx, data->file.res[X],
				data->file.res[Y]);
		if ((err = calcul_img(data)))
			return (err);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img,
				0, 0);
	}
	(void)data;
	return (err);
}

int		c3d_key(int key, t_gnrl *data)
{
	if (key == 65307)
		exit(0);
/*	if (key == 65361 && i->cams->prev)
	if (key == 65363 && info->cams->next)
*/	(void)data;
	return (0);
}

int		c3d_loop(t_gnrl *data)
{
	mlx_key_hook(data->mlx.win, c3d_key, data);
	mlx_loop_hook(data->mlx.mlx, c3d_show, data);
	printf("%p | %p \n", data->mlx.mlx, data->mlx.win);
	mlx_loop(data->mlx.mlx);
	return (0);
}
