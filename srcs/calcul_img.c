/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 18:50:51 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 12:51:15 by user42           ###   ########.fr       */
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

static int			find_wall(t_ray *r, t_gnrl *data, int i)
{
	int	stop;
	int	dist;

	stop = 1;
	dist = 0;
	while (stop)
	{
		if (r->side[X] < r->side[Y])
		{
			r->side[X] += r->delta[X];
			r->pos[X] += r->gap[X];
			r->wall = 1 + (r->gap[X] > 0 ? 1 : 0);
			stop = 1;
		}
		else
		{
			r->side[Y] += r->delta[Y];
			r->pos[Y] += r->gap[Y];
			r->wall = 3 + (r->gap[Y] > 0 ? 1 : 0);
			stop = 2;
		}
		if (r->map->map[r->pos[X]][r->pos[Y]] == '1')
		{
			data->player.map[r->pos[X]][r->pos[Y]] = 2;
			stop = 0;
		}
		else if (r->map->map[r->pos[X]][r->pos[Y]] == '2')
		{
			if (sprite_seen(data, r, stop, i))
				return (4);
		}
		else
			data->player.map[r->pos[X]][r->pos[Y]] = 1;
		if (dist++ > 400)
			stop = 0;
	}
	fflush(stdout);
	return (0);
}
/*
static unsigned int	find_color(t_tex *t, int id)
{
	if (t->id == id)
		return (t->color);
	return (find_color(t->next, id));
}
*/
static void			calcul_tex(t_ray *r, t_gnrl *data, int top, int i)
{
	int		j;
	t_tex	*tex;
	int		bottom;

	bottom = top - 2 * (top - data->file.res[Y] / 2);
	tex = find_tex(r->wall, data);
	if (r->wall > 2)
		r->wallx = r->start[X] + /*r->dist * */r->ray[X] * ((r->pos[Y] - r->start[Y] + (1. - r->gap[Y]) / 2) / r->ray[Y]);
	else
		r->wallx = r->start[Y] + /*r->dist * */r->ray[Y] * ((r->pos[X] - r->start[X] + (1. - r->gap[X]) / 2.) / r->ray[X]);
	r->wallx -= (int)r->wallx;
	r->tex[X] = (int)(tex->width * r->wallx);
	if (r->wall <= 2 && r->ray[X] > 0)
		r->tex[X] = tex->width - r->tex[X] - 1;
	else if (r->wall > 2 && r->ray[Y] < 0)
		r->tex[X] = tex->width - r->tex[X] - 1;
	j = 0;
//	printf("bottom %d\ttop %d\tcolonne %d\n", bottom, top, i);
	while (j < data->file.res[Y])
	{
	//	printf("bottom %d\ti %d\ttop %d\tres %d\thauteur mur %d\thauteur texture %d\ntex[X] = %f\ttex[Y] = %f\n", bottom, j, top, data->file.res[Y], r->h, tex->height, r->tex[X], r->tex[Y]);
		if (j < bottom)
			data->mlx.line[(j++ * data->mlx.size) + i] = data->file.ceiling;
		else if (j >= bottom && j < top)
		{
			r->tex[Y] = (j * 2 - data->file.res[Y] + r->h) * (tex->height / 2)
				/ r->h;
			data->mlx.line[(j++ * data->mlx.size) + i] =
				tex->line[(int)(r->tex[Y]) * tex->size + (int)(r->tex[X])];
		}
		else if (j >= top)
			data->mlx.line[(j++ * data->mlx.size) + i] = data->file.floor;
	}
}

static void			put_columns(t_gnrl *data, t_ray r, int i)
{
	int				bottom;
	int				top;
	unsigned int	color;
	int				j;

	r.h = (int)(data->file.res[Y] / r.dist);
	top = (int)(r.h / 2 + data->file.res[Y] / 2);
	top = (top > data->file.res[Y] ? data->file.res[Y] : top);
	if (is_textured(r, data))
	{
		calcul_tex(&r, data, top, i);
		return ;
	}
	bottom = (int)(-r.h / 2 + data->file.res[Y] / 2);
	bottom = (bottom < 0 ? 0 : bottom);
	if (r.wall == 1)
		color = 0xaa5050;
	if (r.wall == 2)
		color = 0x50aa50;
	if (r.wall == 3)
		color = 0x5050aa;
	if (r.wall == 4)
		color = 0x50aaaa;
	j = 0;
//	printf("bottom %d\ttop %d\tcolonne %d\thauteur mur %d\n", bottom, top, i, h);
	while (j < data->file.res[Y])
	{
		if (j < bottom)
			data->mlx.line[(j++ * data->mlx.size) + i] = data->file.ceiling;
		else if (j >= bottom && j < top)
			data->mlx.line[(j++ * data->mlx.size) + i] = color;
		else if (j >= top)
			data->mlx.line[(j++ * data->mlx.size) + i] = data->file.floor;
	}
}

int					calcul_img(t_gnrl *data)
{
	t_ray	r;
	int		i;

	i = -1;
	ft_bzero((void *)&r, sizeof(t_ray));
	map_cpy(data->player.map, data->file.map);
	r.map = &data->file.map;
	while (++i < data->file.res[X])
	{
		r.pos[X] = (int)data->player.pos[X];
		r.pos[Y] = (int)data->player.pos[Y];
		data->player.map[r.pos[X]][r.pos[Y]] = 'H';
		r.start[X] = data->player.pos[X];
		r.start[Y] = data->player.pos[Y];
//		printf("dist %f\t%c%c%c%c%c\n", r.dist, r.map.map[r.pos[X]][r.pos[Y] - 2], r.map.map[r.pos[X]][r.pos[Y] - 1], r.map.map[r.pos[X]][r.pos[Y]], r.map.map[r.pos[X]][r.pos[Y] + 1], r.map.map[r.pos[X]][r.pos[Y] + 2]);
		r.ratio = (2. * (double)i / (double)(data->file.res[X])) - 1.;
		//printf("%f\n", r.ratio);
		r.ray[X] = data->player.dir[X] + data->player.plane[X] * r.ratio;
		r.ray[Y] = data->player.dir[Y] + data->player.plane[Y] * r.ratio;
		r.delta[X] = sqrt(1. + pow(r.ray[Y] / r.ray[X], 2));
		r.delta[Y] = sqrt(1. + pow(r.ray[X] / r.ray[Y], 2));
		//printf("%f %f\n", r.delta[X], r.delta[Y]);
		set_side(&r);
		if (find_wall(&r, data, i))
			return (4);
		if (r.wall <= 2)
			r.dist = 2 * abs_d((r.pos[X] - r.start[X] + (1. - r.gap[X]) / 2.) / r.ray[X]);
		else
			r.dist = 2 * abs_d((r.pos[Y] - r.start[Y] + (1. - r.gap[Y]) / 2.) / r.ray[Y]);
		data->player.dists[i] = r.dist;
		put_columns(data, r, i);
	}
//	printf("\r%.20f", sqrt(pow(data->player.plane[X], 2) + pow(data->player.plane[Y], 2)));
	put_sprite(data, data->player.sprite);
	data->player.sprite = NULL;
	show_map(data);
//	printf("\rpos = [%f;%f]", data->player.pos[X], data->player.pos[Y]);
	return (0);
}
