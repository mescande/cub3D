/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:34:34 by user42            #+#    #+#             */
/*   Updated: 2021/01/24 11:42:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_sprite(t_sprite *list, t_sprite *new)
{
	if (list->next)
		add_sprite(list->next, new);
	else
		list->next = new;
}

int			sprite_seen(t_gnrl *data, t_ray *r, int ind, int i)
{
	t_sprite	*s;
	double		dist;

	if (data->player.sprite)
	{
		data->player.map[r->pos[X]][r->pos[Y]] = 3;
		s = data->player.sprite;
		dist = (ind == 1 ? r->side[X] - r->delta[X] : r->side[Y] - r->delta[Y]);
		while (s && dist)
		{
			if (s->pos[X] == r->pos[X] && s->pos[Y] == r->pos[Y])
			{
				if (s->dist > dist)
					s->dist = dist;
				return (0);
			}
			s = s->next;
		}
	}
	if (!(s = (t_sprite *)ft_memalloc(sizeof(t_sprite))))
		return (4);
//	s->id = r->player->map[r->pos[X]][r->pos[Y]];
	s->id = 5;
	s->pos[X] = r->pos[X];
	s->pos[Y] = r->pos[Y];
	s->dist = (ind == 1 ? r->side[X] - r->delta[X] : r->side[Y] - r->delta[Y]);
	s->column = i;
	if (data->player.sprite)
		add_sprite(data->player.sprite, s);
	else
		data->player.sprite = s;
	return (0);
}

static int	sort_it(t_sprite *elem, t_sprite *next)
{
	t_sprite	*s;

	if (elem == NULL || next == NULL)
		return (0);
	if (elem->dist < next->dist)
	{
		s = elem;
		elem = next;
		next = s;
		next->next = elem->next;
		elem->next = next;
		return (1);
	}
	if (sort_it(next, next->next))
		return (sort_it(elem, next));
	return (0);
}

void		sprite_sort(t_gnrl *data)
{
	t_sprite	*s[3];

	if (!data->player.sprite || !data->player.sprite->next)
		return ;
	s[0] = data->player.sprite;
	s[1] = s[0]->next;
	if (s[0]->dist < s[1]->dist)
	{
		s[0]->next = s[1]->next;
		s[1]->next = s[0];
		data->player.sprite = s[1];
		s[1] = s[0];
		s[0] = data->player.sprite; // ATTENTION, ca marche pas, il faut sortir
	} // le if de la boucle pour le 1er.... -> recursif ??
	sort_it(s[0], s[1]);
}
/*
void		put_sprite(t_gnrl *data, t_sprite *s)
{
	int		h;
	double	bottom;
	double	top;
	double	t[2];
	int		i;
	t_tex	*tex;

	if (!s)
		return ;
	if (s->next)
		put_sprite(data, s->next);
	h = (int)(data->file.res[Y] / s->dist);
	top = (int)(h / 2 + data->file.res[Y] / 2);
	top = (top > data->file.res[Y] ? data->file.res[Y] : top);
	bottom = top - 2 * (top - data->file.res[Y] / 2);
	h = (int)(data->file.res[X] / s->dist);
	tex = find_tex(s->id, data);
	while (bottom < top)
	{
		i = 0;
		t[X] = (bottom * 2 - data->file.res[Y] + h) * (tex->height / 2) / h;
		while (i < h && i + s->column < data->file.res[X])
		{
			t[Y] = (i * 2 - data->file.res[Y] + h);
	printf("%d\n", __LINE__);
	printf("%x, %d\n", data->mlx.line[(int)((bottom * data->mlx.size) + i + s->column)], (int)((bottom * data->mlx.size) + i + s->column));
			data->mlx.line[(int)((bottom * data->mlx.size) + i + s->column)] =
				tex->line[(int)((t[X] * tex->size) + t[Y])];
	printf("%d\n", __LINE__);
			i++;
		}
		bottom++;
	}
}
*/
void		put_sprite(t_gnrl *data, t_sprite *s)
{
	int		size[2];
	int		born[2];
	double	t[2];
	int		i[2];
	t_tex	*tex;

	if (!s)
		return ;
	if (s->next)
		put_sprite(data, s->next);
	size[0] = (int)(data->file.res[Y] / s->dist);
	born[1] = (int)(data->file.res[Y] / 2 + size[0] / 2);
	born[0] = (int)(data->file.res[Y] / 2 - size[0] / 2);
	born[1] = (born[1] > data->file.res[Y] ? data->file.res[Y] : born[1]);
	born[0] = (born[0] < 0 ? 0 : born[0]);
	size[1] = (int)(data->file.res[X] / s->dist);
	tex = find_tex(s->id, data);
//	printf("%p\n", tex);
	i[0] = 0;
	while (born[0] + i[0] < born[1])
	{
		t[X] = (double)tex->height * (double)i[0] / (double)size[0];
		i[1] = 0;
		while (i[1] < size[1] && i[1] + s->column < data->file.res[X])
		{
			t[Y] = (double)tex->width * (double)i[1] / (double)size[1];
			if (tex->line[(int)(t[X] * tex->size + t[Y])])
				data->mlx.line[(born[0] + i[0]) * data->mlx.size + s->column +
					i[1]] =	tex->line[(int)(t[X] * tex->size + t[Y])];
			i[1]++;
		}
		i[0]++;
	}
	free(s);
	s = NULL;
}
