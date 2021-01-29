/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:34:34 by user42            #+#    #+#             */
/*   Updated: 2021/01/29 20:34:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite *add_sprite(t_sprite *sp_list, t_sprite *new_sp)
{
	const t_sprite *head = sp_list;

	if (!sp_list || new_sp->dist > sp_list->dist)
	{
		new_sp->next = sp_list;
		return (new_sp);
	}
	while (sp_list->next && new_sp->dist < sp_list->next->dist)
		sp_list = sp_list->next;
	new_sp->next = sp_list->next;
	sp_list->next = new_sp;
	return ((t_sprite *)head);
}

int			sprite_seen(t_gnrl *data, t_ray *r, int ind, int i)
{
	t_sprite	*s;
	double		tmp;
	double		tran[2];

	(void)i;
	(void)ind;
	if ((s = data->player.sprite))
		while (s)
		{
			if (s->pos[X] == r->pos[X] && s->pos[Y] == r->pos[Y])
				return (0);
			s = s->next;
		}
	if (!(s = (t_sprite *)ft_memalloc(sizeof(t_sprite))))
		return (4);
	data->player.map[r->pos[X]][r->pos[Y]] = 3;
	s->id = 5;
	s->pos[X] = r->pos[X];
	s->pos[Y] = r->pos[Y];
	tran[X] = s->pos[X] - data->player.pos[X] + 0.5;
	tran[Y] = s->pos[Y] - data->player.pos[Y] + 0.5;
	tmp = tran[Y];
	tran[Y] = r->idet * (data->player.dir[X] * tmp - data->player.dir[Y] * tran[X]);
	tran[X] = r->idet * (data->player.plane[Y] * tran[X] - data->player.plane[X] * tmp);
	s->column = (int)((double)data->file.res[X] / 2. * (1. + tran[Y] / tran[X]));
	s->dist = 2 * tran[X];
	s->next = NULL;
	data->player.sprite = add_sprite(data->player.sprite, s);
	return (0);
}

void		put_sprite(t_gnrl *data, t_sprite *s)
{
	int		size[2];
	int		born[2];
	double	t[2];
	int		i[3];
	t_tex	*tex;

	if (!s)
		return ;
	size[0] = (int)(data->file.res[Y] / s->dist);
	born[1] = (int)(data->file.res[Y] / 2 + size[0] / 2);
	born[0] = (int)(data->file.res[Y] / 2 - size[0] / 2);
	born[1] = (born[1] > data->file.res[Y] ? data->file.res[Y] : born[1]);
	born[0] = (born[0] < 0 ? 0 : born[0]);
	size[1] = (int)(data->file.res[X] / s->dist);
	tex = find_tex(s->id, data);
	i[1] = 0;
	i[2] = s->column - size[1] / 2;
	if (i[2] < 0)
	{
		i[1] -= i[2];
		i[2] -= i[2];
	}
	while (i[1] < size[1] && i[1] + s->column - size[1] / 2 < data->file.res[X])
	{
		t[Y] = (double)tex->width * (double)i[1] / ((double)size[1]);
		i[0] = 0;
		while (born[0] + i[0] < born[1]
				&& data->player.dists[i[1] + s->column - size[1] / 2] > s->dist)
		{
			t[X] = (double)((i[0] + born[0]) - data->file.res[Y] / 2 + size[0] / 2)
				* (double)tex->height / (((double)size[0]));
			if (tex->line[(int)(t[X]) * tex->size + (int)(t[Y])])
				data->mlx.line[(born[0] + i[0]) * data->mlx.size + i[1] +
					s->column - size[1] / 2] = 
					tex->line[(int)(t[X]) * tex->size + (int)(t[Y])];
			i[0]++;
		}
		i[1]++;
	}
	put_sprite(data, s->next);
	free(s);
	s = NULL;
}
