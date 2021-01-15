/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 00:04:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 16:49:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_resolution(t_file *file)
{
	char	*tmp;

	if (file->res[X] != 0)
		return (14);
	tmp = ft_strtok(NULL, " \t");
	if (tmp == NULL)
		return (12);
	file->res[X] = ft_atoi(tmp);
	tmp = ft_strtok(NULL, " \t");
	if (tmp == NULL)
		return (12);
	file->res[Y] = ft_atoi(tmp);
	tmp = ft_strtok(NULL, " \t");
	if (tmp != NULL)
		return (13);
	return (0);
}

void	add_textures(t_file *file, t_tex *tree, t_tex *new)
{
	if (!tree)
		file->textures = new;
	else if (!(tree->next))
		tree->next = new;
	else
		add_textures(file, tree->next, new);
}

/*
**	NO,	SO,	WE,	EA,	S
**	0	1	2	3	4
*/

int		set_textures(t_file *file, char id)
{
	t_tex	*new;
	char	*tmp;

	new = file->textures;
	while (new)
	{
		if (new->id == id)
			return (16 + id);
		new = new->next;
	}
	if (!(new = (t_tex *)ft_memalloc(sizeof(t_tex))))
		return (4);
	tmp = ft_strtok(NULL, " \t");
	if (tmp == NULL)
		return (22 + id);
	new->name = tmp;
	tmp = ft_strtok(NULL, " \t");
	if (tmp != NULL)
		return (28 + id);
	if (!(new->name = ft_strdup(new->name)))
		return (4);
	new->id = id;
	add_textures(file, file->textures, new);
	return (0);
}

int		verif_color(void)
{
	int		val;
	char	*tmp;

	tmp = ft_strtok(NULL, ",; \t.");
	if (tmp == NULL)
		return (34 + 255);
	val = ft_atoi(tmp);
	if (val < 0 || 255 < val)
		return (40 + 255);
	return (val);
}

int		set_colors(t_file *file, char id)
{
	int		val;
	char	*tmp;

	if (id == 0)
		tmp = file->floor;
	else
		tmp = file->ceiling;
	if ((val = verif_color()) > 255)
		return (val - 255 + id);
	tmp[0] = (char)val;
	if ((val = verif_color()) > 255)
		return (val - 255 + id);
	tmp[1] = (char)val;
	if ((val = verif_color()) > 255)
		return (val - 255 + id);
	tmp[2] = (char)val;
	tmp = ft_strtok(NULL, " \t");
	if (tmp != NULL)
		return (37 + id);
	return (0);
}
