/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 18:50:51 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 16:38:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				set_side(t_ray *r)
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
		react_map_char(r, data, &stop);
		if (dist++ > 400)
			stop = 0;
	}
}

static void			calcul_tex(t_ray *r, t_gnrl *data, int top, int i)
{
	int		j;
	t_tex	*tex;
	int		bottom;

	bottom = top - 2 * (top - data->file.res[Y] / 2);
	tex = find_tex(r->wall, data);
	init_tex_values(r, tex);
	if (r->wall <= 2 && r->ray[X] > 0)
		r->tex[X] = tex->width - r->tex[X] - 1;
	else if (r->wall > 2 && r->ray[Y] < 0)
		r->tex[X] = tex->width - r->tex[X] - 1;
	j = 0;
	while (j < data->file.res[Y])
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
	color = set_color(r);
	j = 0;
	while (j < data->file.res[Y])
		if (j < bottom)
			data->mlx.line[(j++ * data->mlx.size) + i] = data->file.ceiling;
		else if (j >= bottom && j < top)
			data->mlx.line[(j++ * data->mlx.size) + i] = color;
		else if (j >= top)
			data->mlx.line[(j++ * data->mlx.size) + i] = data->file.floor;
}

int					calcul_img(t_gnrl *data)
{
	t_ray	r;
	int		i;

	i = -1;
	init_img(&r, data);
	while (++i < data->file.res[X])
	{
		init_ray(&r, data, i);
		find_wall(&r, data);
		if (r.wall <= 2)
			r.dist = 2 * abs_d((r.pos[X] - r.start[X] + (1. - r.gap[X]) / 2.)
					/ r.ray[X]);
		else
			r.dist = 2 * abs_d((r.pos[Y] - r.start[Y] + (1. - r.gap[Y]) / 2.)
					/ r.ray[Y]);
		data->player.dists[i] = r.dist;
		put_columns(data, r, i);
	}
	if (data->player.tree)
		put_sprite(data, data->player.tree);
	show_map(data);
	return (0);
}
