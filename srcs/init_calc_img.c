/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_calc_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 16:17:53 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 16:59:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				init_img(t_ray *r, t_gnrl *data)
{
	ft_bzero((void *)r, sizeof(t_ray));
	map_cpy(data->player.map, data->file.map);
	r->map = &data->file.map;
	r->idet = 1. / (data->player.plane[Y] * data->player.dir[X]
			- data->player.plane[X] * data->player.dir[Y]);
	data->cur_sp = data->sp;
	data->player.tree = NULL;
}

void				init_ray(t_ray *r, t_gnrl *data, int i)
{
	r->pos[X] = (int)data->player.pos[X];
	r->pos[Y] = (int)data->player.pos[Y];
	data->player.map[r->pos[X]][r->pos[Y]] = 'H';
	r->start[X] = data->player.pos[X];
	r->start[Y] = data->player.pos[Y];
	r->ratio = (2. * (double)i / (double)(data->file.res[X])) - 1.;
	r->ray[X] = data->player.dir[X] + data->player.plane[X] * r->ratio;
	r->ray[Y] = data->player.dir[Y] + data->player.plane[Y] * r->ratio;
	r->delta[X] = sqrt(1. + pow(r->ray[Y] / r->ray[X], 2));
	r->delta[Y] = sqrt(1. + pow(r->ray[X] / r->ray[Y], 2));
	set_side(r);
}

unsigned int		set_color(t_ray r)
{
	unsigned int	color;

	if (r.wall == 1)
		color = 0xaa5050;
	if (r.wall == 2)
		color = 0x50aa50;
	if (r.wall == 3)
		color = 0x5050aa;
	if (r.wall == 4)
		color = 0x50aaaa;
	return (color);
}

void				init_tex_values(t_ray *r, t_tex *tex)
{
	if (r->wall > 2)
		r->wallx = r->start[X] + r->ray[X]
			* ((r->pos[Y] - r->start[Y] + (1. - r->gap[Y]) / 2) / r->ray[Y]);
	else
		r->wallx = r->start[Y] + r->ray[Y]
			* ((r->pos[X] - r->start[X] + (1. - r->gap[X]) / 2.) / r->ray[X]);
	r->wallx -= (int)r->wallx;
	r->tex[X] = (int)(tex->width * r->wallx);
}

void				react_map_char(t_ray *r, t_gnrl *data, int *stop)
{
	if (r->map->map[r->pos[X]][r->pos[Y]] == '1')
	{
		data->player.map[r->pos[X]][r->pos[Y]] = 2;
		*stop = 0;
	}
	else if (r->map->map[r->pos[X]][r->pos[Y]] == '2')
	{
		sprite_seen(data, r);
	}
	else
		data->player.map[r->pos[X]][r->pos[Y]] = 1;
}
