/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 23:05:58 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 23:28:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		show_textured(t_gnrl *data, t_sprite *s)
{
	int		size[4];
	double	t[2];
	int		i[3];
	t_tex	*tex;

	init_show(size, data, i, s);
	tex = find_tex(s->id, data);
	while (i[1] < size[1] && i[1] + s->column - size[1] / 2 < data->file.res[X])
	{
		t[Y] = (double)tex->width * (double)i[1] / ((double)size[1]);
		i[0] = 0;
		while (size[2] + i[0] < size[3]
				&& data->player.dists[i[1] + s->column - size[1] / 2] > s->dist)
		{
			t[X] = (double)((i[0] + size[2]) - data->file.res[Y] / 2
					+ size[0] / 2) * (double)tex->height / (((double)size[0]));
			if (tex->line[(int)(t[X]) * tex->size + (int)(t[Y])])
				data->mlx.line[(size[2] + i[0]) * data->mlx.size + i[1] +
					s->column - size[1] / 2] =
					tex->line[(int)(t[X]) * tex->size + (int)(t[Y])];
			i[0]++;
		}
		i[1]++;
	}
}

void		show_colored(t_gnrl *data, t_sprite *s)
{
	int		size[4];
	int		i[3];

	init_show(size, data, i, s);
	while (i[1] < size[1] && i[1] + s->column - size[1] / 2 < data->file.res[X])
	{
		i[0] = 0;
		while (size[2] + i[0] < size[3]
				&& data->player.dists[i[1] + s->column - size[1] / 2] > s->dist)
		{
			data->mlx.line[(size[2] + i[0]) * data->mlx.size + i[1] +
					s->column - size[1] / 2] = set_color(5);
			i[0]++;
		}
		i[1]++;
	}
}
