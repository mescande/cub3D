/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 18:50:51 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 22:04:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			set_side(t_ray *r)
{
	if (r->ray[X] < 0)
	{
		r->gap[X] = -1;
	 	r->side[X] = (r->start[X] - r->pos[X]) * r->delta[X];
	}
	else
	{
		r->gap[X] = 1;
	 	r->side[X] = (r->pos[X] + 1. - r->start[X]) * r->delta[X];
	}
	if (r->ray[Y] < 0)
	{
		r->gap[Y] = -1;
		r->side[Y] = (r->start[Y] - r->pos[Y]) * r->delta[Y];
	}
	else
	{
		r->gap[Y] = 1;
		r->side[Y] = (r->pos[Y] + 1. - r->start[Y]) * r->delta[Y];
	}
}

static void			find_wall(t_ray *r, t_gnrl *data)
{
	int	stop;
//	static int k = 1;
	int i;

	i = 0;
	(void)data;
	stop = 0;
	while (!stop)
	{
		if (r->side[X] < r->side[Y])
		{
			r->side[X] += r->delta[X];
			r->pos[X] += r->gap[X];
			r->wall = 1 + (r->gap[X] > 0 ? 1 : 0);
		}
		else
		{
			r->side[Y] += r->delta[Y];
			r->pos[Y] += r->gap[Y];
			r->wall = 3 + (r->gap[Y] > 0 ? 1 : 0);
		}
		if (r->map->map[r->pos[X]][r->pos[Y]] == '1')
		{
			r->player->map[r->pos[X]][r->pos[Y]] = '9';
			stop = 1;
		}
		else
			r->player->map[r->pos[X]][r->pos[Y]] = '8';
		//if (k)
//		printf("side[X] = %f\tside[Y] = %f\n", r->side[X], r->side[Y]);
//		printf("%d   %d %d\n", i, r->pos[X], r->pos[Y]);
		fflush(stdout);
		i++;
	}
//	k = 0;
}

static unsigned int	find_color(t_tex *t, int id)
{
	if (t->id == id)
		return (t->color);
	return (find_color(t->next, id));
}

static void			put_columns(t_gnrl *data, t_ray r, int i)
{
	int				h;
	int				bottom;
	int				top;
	unsigned int	color;
	unsigned int	ceil;
	unsigned int	floor;
	int				j;

	h = (int)(data->file.res[Y] / r.dist);
	bottom = (int)(-h / 2 + data->file.res[Y] / 2);
	bottom = (bottom < 0 ? 0 : bottom);
	top = (int)(h / 2 + data->file.res[Y] / 2);
	top = (top > data->file.res[Y] ? data->file.res[Y] : top);
	color = find_color(data->file.textures, r.wall);
	if (r.wall == 1)
		color = 0xaa5050;
	if (r.wall == 2)
		color = 0x50aa50;
	if (r.wall == 3)
		color = 0x5050aa;
	if (r.wall == 4)
		color = 0x50aaaa;
	ceil = data->file.ceiling;
	floor = data->file.floor;
	j = 0;
//	printf("bottom %d\ttop %d\tcolonne %d\thauteur mur %d\n", bottom, top, i, h);
	while (j < data->file.res[Y])
	{
		if (j < bottom)
			data->mlx.line[(j++ * data->mlx.size) + i] = ceil;
		else if (j >= bottom && j < top)
			data->mlx.line[(j++ * data->mlx.size) + i] = color;
		else if (j >= top)
			data->mlx.line[(j++ * data->mlx.size) + i] = floor;
	}

}

int					calcul_img(t_gnrl *data)
{
	t_ray	r;
	int		i;

	i = -1;
	ft_bzero((void *)&r, sizeof(t_ray));
	r.player = &data->player;
	map_cpy(r.player->map, data->file.map);
	r.map = &data->file.map;
	while (++i < data->file.res[X])
	{
		r.pos[X] = (int)r.player->pos[X];
		r.pos[Y] = (int)r.player->pos[Y];
		r.player->map[r.pos[X]][r.pos[Y]] = 'H';
		r.start[X] = r.player->pos[X];
		r.start[Y] = r.player->pos[Y];
//		printf("dist %f\t%c%c%c%c%c\n", r.dist, r.map.map[r.pos[X]][r.pos[Y] - 2], r.map.map[r.pos[X]][r.pos[Y] - 1], r.map.map[r.pos[X]][r.pos[Y]], r.map.map[r.pos[X]][r.pos[Y] + 1], r.map.map[r.pos[X]][r.pos[Y] + 2]);
		r.ratio = (2. * (double)i / (double)(data->file.res[X])) - 1.;
		//printf("%f\n", r.ratio);
		r.ray[X] = r.player->dir[X] + r.player->plane[X] * r.ratio;
		r.ray[Y] = r.player->dir[Y] + r.player->plane[Y] * r.ratio;
		r.delta[X] = sqrt(1. + pow(r.ray[Y] / r.ray[X], 2));
		r.delta[Y] = sqrt(1. + pow(r.ray[X] / r.ray[Y], 2));
		//printf("%f %f\n", r.delta[X], r.delta[Y]);
		set_side(&r);
		find_wall(&r, data);
		if (r.wall <= 2)
			r.dist = 2 * abs_d((r.pos[X] - r.start[X] + (1. - r.gap[X]) / 2.) / r.ray[X]);
		else
			r.dist = 2 * abs_d((r.pos[Y] - r.start[Y] + (1. - r.gap[Y]) / 2.) / r.ray[Y]);
		put_columns(data, r, i);
	}
	show_map(data);
	return (0);
}
