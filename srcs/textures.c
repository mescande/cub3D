/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:06:38 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 17:57:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_textured(t_ray r, t_gnrl *data)
{
	t_tex	*p;

	p = data->file.textures;
	while (p)
	{
		if (p->name && p->id == r.wall)
			return (1);
		p = p->next;
	}
	return (0);
}

t_tex	*find_tex(int id, t_gnrl *data)
{
	t_tex	*p;

	p = data->file.textures;
	while (p)
	{
		if (p->id == id)
			return (p);
		p = p->next;
	}
	return (0);
}
