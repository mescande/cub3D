/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:34:34 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 18:43:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*add_sprite(t_sprite *sp_list, t_sprite *new_sp)
{
	t_sprite	*s;

	if (!sp_list)
		return (new_sp);
	s = sp_list;
	while (1)
		if (new_sp->dist > s->dist)
		{
			if (!s->left)
			{
				s->left = new_sp;
				return (sp_list);
			}
			s = s->left;
		}
		else
		{
			if (!s->right)
			{
				s->right = new_sp;
				return (sp_list);
			}
			s = s->right;
		}
}

void		sprite_seen(t_gnrl *data, t_ray *r)
{
	t_sprite	*s;
	double		tmp;
	double		tran[2];

	if (data->player.map[r->pos[X]][r->pos[Y]] == 3)
		return ;
	s = data->cur_sp;
	data->cur_sp++;
	data->player.map[r->pos[X]][r->pos[Y]] = 3;
	s->id = 5;
	s->pos[X] = r->pos[X];
	s->pos[Y] = r->pos[Y];
	tran[X] = s->pos[X] - data->player.pos[X] + 0.5;
	tran[Y] = s->pos[Y] - data->player.pos[Y] + 0.5;
	tmp = tran[Y];
	tran[Y] = r->idet * (data->player.dir[X] * tmp
			- data->player.dir[Y] * tran[X]);
	tran[X] = r->idet * (data->player.plane[Y] * tran[X]
			- data->player.plane[X] * tmp);
	s->column = (int)((double)data->file.res[X] / 2. * (1 + tran[Y] / tran[X]));
	s->dist = 2 * tran[X];
	s->left = NULL;
	s->right = NULL;
	data->player.tree = add_sprite(data->player.tree, s);
}

static void	init_print_sprite(int *size, t_gnrl *data, int *i, t_sprite *s)
{
	size[0] = (int)(data->file.res[Y] / s->dist);
	size[3] = (int)(data->file.res[Y] / 2 + size[0] / 2);
	size[2] = (int)(data->file.res[Y] / 2 - size[0] / 2);
	size[3] = (size[3] > data->file.res[Y] ? data->file.res[Y] : size[3]);
	size[2] = (size[2] < 0 ? 0 : size[2]);
	size[1] = (int)(data->file.res[X] / s->dist);
	i[1] = 0;
	i[2] = s->column - size[1] / 2;
	if (i[2] < 0)
	{
		i[1] -= i[2];
		i[2] -= i[2];
	}
}

void		print_sprite(t_gnrl *data, t_sprite *s)
{
	int		size[4];
	double	t[2];
	int		i[3];
	t_tex	*tex;

	init_print_sprite(size, data, i, s);
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

void		put_sprite(t_gnrl *data, t_sprite *s)
{
	if (s->left)
		put_sprite(data, s->left);
	print_sprite(data, s);
	if (s->right)
		put_sprite(data, s->right);
}
