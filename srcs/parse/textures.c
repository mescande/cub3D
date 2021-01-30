/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:14:53 by user42            #+#    #+#             */
/*   Updated: 2021/01/30 15:16:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_textures(t_file *file, t_tex *tree, t_tex *new)
{
	if (!tree)
		file->textures = new;
	else if (!(tree->next))
		tree->next = new;
	else
		add_textures(file, tree->next, new);
}

int		open_texture(t_gnrl *data)
{
	t_tex	*p;
	int		a;

	p = data->file.textures;
	while (p)
	{
		if (ft_strcmp(p->name + ft_strlen(p->name) - 4, ".xpm"))
			return (50 + p->id - 1);
		if (!(p->img = mlx_xpm_file_to_image(data->mlx.mlx, p->name, &p->width,
					&p->height)))
			return (55 + p->id - 1);
		p->line = (unsigned int *)mlx_get_data_addr(p->img, &a, &p->size, &a);
		p->size = p->size / 4;
		p = p->next;
	}
	return (0);
}

/*
**	NO,	SO,	WE,	EA,	S
**	1	2	3	4	4
*/

int		set_textures(t_file *file, char id, char *sep)
{
	t_tex	*new;
	char	*tmp;

	new = file->textures;
	while (new)
	{
		if (new->id == id)
			return (15 + id);
		new = new->next;
	}
	if (!(new = (t_tex *)ft_memalloc(sizeof(t_tex))))
		return (4);
	tmp = ft_strtok(NULL, sep);
	if (tmp == NULL)
		return (22 + id);
	new->name = tmp;
	tmp = ft_strtok(NULL, sep);
	if (tmp != NULL)
		return (28 + id);
	if (!(new->name = ft_strdup(new->name)))
		return (4);
	new->id = id;
	add_textures(file, file->textures, new);
	return (0);
}
