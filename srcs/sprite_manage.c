/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:34:34 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 14:16:36 by user42           ###   ########.fr       */
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
	double		dist[3];
//	double		vect[2];

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
//	s->id = r->player->map[r->pos[X]][r->pos[Y]];
	data->player.map[r->pos[X]][r->pos[Y]] = 3;
	s->id = 5;
	s->pos[X] = r->pos[X];
	s->pos[Y] = r->pos[Y];
//	s->dist = (ind == 1 ? r->side[X] - r->delta[X] : r->side[Y] - r->delta[Y]);
	s->dist = sqrt(pow(data->player.pos[X] - s->pos[X] - 0.5 + data->player.dir[X], 2)
			+ pow(data->player.pos[Y] - s->pos[Y] + 0.5 + data->player.dir[Y], 2));
	//dist = norm(player->pos - pos + 0.5);
//	s->column = i;
//	vect[X] = s->pos[X] - data
	dist[0] = sqrt(pow(data->player.plane[X], 2) + sqrt(pow(data->player.plane[Y], 2)));
	dist[1] = sqrt(pow(s->pos[X] - data->player.pos[X] + 0.5, 2)
			+ pow(s->pos[Y] - data->player.pos[Y] + 0.5, 2));
	dist[2] = (double)(
			(
			 (s->pos[X] - data->player.pos[X] + 0.5) 
			* data->player.plane[X] +
			 (s->pos[Y] - data->player.pos[Y] + 0.5)
			* data->player.plane[Y]
			) /	dist[0]);
	s->column = (int)((
				(sqrt(pow(data->player.dir[X], 2) + pow(data->player.dir[Y], 2)) 
				 * dist[2])
				/ sqrt(pow(dist[1], 2) - pow(dist[2], 2)))
			* data->file.res[X] + data->file.res[X] / 2);


	printf("%d = dir * %f / sqrt(%f^2 + dist[2]^2)\r", s->column, dist[2], dist[1]);
	fflush(stdout);
	//colmn = (dot(ray*dist, plane) / norm(plane)) * res[X] + res[X] / 2
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
		s[0] = data->player.sprite;
	}
	sort_it(s[0], s[1]);
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
	i[1] = 0;
	i[2] = s->column - size[1] / 2;
//	printf("\r%d = %d - %d / 2       ", i[2], s->column, size[1]);
//	fflush(stdout);
	if (i[2] < 0)
	{
		i[1] -= i[2];
		i[2] -= i[2];
	}
	while (i[1] < size[1] && i[1] + s->column - size[1] / 2 < data->file.res[X])
	{
//		t[X] = (double)tex->height * (double)i[0] / (double)size[0];
		t[Y] = (double)tex->width * (double)i[1] / ((double)size[1]);
//	printf("t[Y] %f\ti[1] %d\t %d - %d / 2 = %d\n", t[Y], i[1], s->column, size[1], i[1] + s->column - size[1] / 2);
		i[0] = 0;
		while (born[0] + i[0] < born[1]
				&& data->player.dists[i[1] + s->column - size[1] / 2] > s->dist)
		{
			t[X] = (double)((i[0] + born[0]) * 2 - data->file.res[Y] + size[0])
				* (double)tex->height / ((2 *(double)size[0]));
//			printf("img[%d][%d] : tex[%f][%f]\n", born[0] + i[0], s->column + i[1], t[X], t[Y]);
			if (tex->line[(int)(t[X] * tex->size + t[Y])])
				data->mlx.line[(born[0] + i[0]) * data->mlx.size + i[1] +
					s->column - size[1] / 2] = 
					tex->line[(int)(t[X] * tex->size + t[Y])];
			i[0]++;
		}
		i[1]++;
	}
	free(s);
	s = NULL;
}
