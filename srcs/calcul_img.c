/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 18:50:51 by user42            #+#    #+#             */
/*   Updated: 2021/01/16 23:30:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			set_side(t_ray *r)
{
	if (r->ray[X] < 0)
	{
		r->gap[X] = -1;
	 	r->side[X] = (r->ray[X] - r->player.posi[X]) * r->delta[X];
	}
	else
	{
		r->gap[X] = 1;
	 	r->side[X] = ((int)r->ray[X] + 1.0 - r->ray[X]) * r->delta[X];
	}
	if (r->ray[Y] < 0)
	{
		r->gap[Y] = -1;
		r->side[Y] = (r->ray[Y] - (int)r->ray[Y]) * r->delta[Y];
	}
	else
	{
		r->gap[Y] = 1;
		r->side[Y] = ((int)r->ray[Y] + 1.0 - r->ray[Y]) * r->delta[Y];
	}
}

static void			find_wall(t_ray *r)
{
	int	stop;
//	int i;

//	i = 0;
	stop = 0;
	while (!stop)
	{
		if (r->side[X] < r->side[Y])
		{
			r->side[X] += r->delta[X];
			r->pos[X] += r->gap[X];
			r->wall = 1 + (r->gap[X] ? 1 : 0);
		}
		else
		{
			r->side[Y] += r->delta[Y];
			r->pos[Y] += r->gap[Y];
			r->wall = 3 + (r->gap[Y] ? 1 : 0);
		}
		if (r->map.map[r->pos[X]][r->pos[Y]] == '1')
			stop = 1;
//		printf("%d %d\n", i, __LINE__);
//		fflush(stdout);
//		i++;
	}
}

static unsigned int	find_color(t_tex *t, int id)
{
	if (t->id == id)
		return (t->color);
	return (find_color(t->next, id));
}

static void			put_columns(t_gnrl *data, t_ray r, int i, int size)
{
	int				h;
	int				bottom;
	int				top;
	unsigned int	color;
	unsigned int	*line;

	size = 0;
	h = (int)(data->file.res[Y] / r.dist);
	bottom = (int)(-h / 2 + data->file.res[Y] / 2);
	bottom = (bottom < 0 ? 0 : bottom);
	top = (int)(h / 2 + data->file.res[Y] / 2);
	top = (top > data->file.res[Y] ? data->file.res[Y] : top);
	color = find_color(data->file.textures, r.wall);
	color = 0xff0000;
	line = (unsigned int *)mlx_get_data_addr(data->mlx.img, &h, &size, &h);
//	printf("bottom %d\ttop %d\tcolonne %d\n", bottom, top, i);
	while (bottom < top)
		line[(bottom++ * size) + i] = color;
}

int					calcul_img(t_gnrl *data)
{
	t_ray	r;
	int		i;
	int		size;

	i = -1;
	r.i = data->player.pos;
	r.map = data->file.map;
	while (++i < data->file.res[X])
	{
		r.pos[X] = (int)data->player.pos[X];
		r.pos[Y] = (int)data->player.pos[Y];
//		printf("dist %f\t%c%c%c%c%c\n", r.dist, r.map.map[r.pos[X]][r.pos[Y] - 2], r.map.map[r.pos[X]][r.pos[Y] - 1], r.map.map[r.pos[X]][r.pos[Y]], r.map.map[r.pos[X]][r.pos[Y] + 1], r.map.map[r.pos[X]][r.pos[Y] + 2]);
		r.ratio = 2 * i / (double)(data->file.res[X]) - 1;
		r.ray[X] = r.i[X] + r.player.plane[X] * r.ratio;
		r.ray[Y] = r.i[Y] + r.player.plane[Y] * r.ratio;
		r.delta[X] = sqrt(1 + pow(r.ray[Y] / r.ray[X], 2));
		r.delta[Y] = sqrt(1 + pow(r.ray[X] / r.ray[Y], 2));
		set_side(&r);
		find_wall(&r);
		if (r.wall <= 2)
			r.dist = abs_d((r.pos[X] - r.i[X] + (1 - r.gap[X]) / 2) / r.ray[X]);
		else
			r.dist = abs_d((r.pos[Y] - r.i[Y] + (1 - r.gap[Y]) / 2) / r.ray[Y]);
		put_columns(data, r, i, (size = 0));
	}
	return (0);
}
