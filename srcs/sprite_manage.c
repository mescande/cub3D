/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:34:34 by user42            #+#    #+#             */
/*   Updated: 2021/01/22 09:04:15 by user42           ###   ########.fr       */
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

int		sprite_seen(t_gnrl *data, t_ray *r, int ind)
{
	t_sprite	*s;
	double		dist;

	if (data->player.sprite)
	{
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
	s->id = r->player->map[r->pos[X]][r->pos[Y]];
	r->player->map[r->pos[X]][r->pos[Y]] = 3;
	s->pos[X] = r->pos[X];
	s->pos[Y] = r->pos[Y];
	s->dist = (ind == 1 ? r->side[X] - r->delta[X] : r->side[Y] - r->delta[Y]);
	if (data->player.sprite)
		add_sprite(data->player.sprite, s);
	else
		data->player.sprite = s;
	return (0);
}

int		sort_it(t_sprite *elem, t_sprite *next)
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

void		put_sprite(t_gnrl *data, t_sprite *s)
{
	if (s->next)
		put_sprite(data, s->next);
}
