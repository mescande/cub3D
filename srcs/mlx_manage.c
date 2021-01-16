/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescande <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:50:08 by mescande          #+#    #+#             */
/*   Updated: 2021/01/16 12:17:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		start_mlx(t_gnrl *data)
{
	int		x;
	int		y;
	t_mlx	*w;

	w = &data->mlx;
	if (!(w->mlx = mlx_init()))
		return (7);
	mlx_get_screen_size(w->mlx, &x, &y);
	data->file.res[X] = (x > data->file.res[X] ? data->file.res[X] : x);
	data->file.res[Y] = (y > data->file.res[Y] ? data->file.res[Y] : y);
	if (!(w->win = mlx_new_window(w->mlx, data->file.res[X],
					data->file.res[Y], "cub3D by mescande")))
		return (9);
	return (0);
}

void	end_mlx(t_mlx *win)
{
	if (win->win)
	{
		mlx_clear_window(win->mlx, win->win);
		mlx_destroy_window(win->mlx, win->win);
		win->win = NULL;
	}
	if (win->mlx)
	{
		free(win->mlx);
		win->mlx = NULL;
	}
}
