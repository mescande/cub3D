/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 00:04:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 18:05:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_resolution(t_file *file, char id, char *sep)
{
	char	*tmp;

	(void)id;
	if (file->res[X] != 0)
		return (14);
	tmp = ft_strtok(NULL, sep);
	if (tmp == NULL)
		return (12);
	file->res[X] = ft_atoi(tmp);
	tmp = ft_strtok(NULL, sep);
	if (tmp == NULL)
		return (12);
	file->res[Y] = ft_atoi(tmp);
	tmp = ft_strtok(NULL, sep);
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

int		open_texture(t_gnrl *data)
{
	t_tex	*p;
	int		a;

	p = data->file.textures;
	while (p)
	{
		if (ft_strcmp(p->name + ft_strlen(p->name) - 4, ".xpm"))
			return (50 + p->id -1 );
		if (!(p->img = mlx_xpm_file_to_image(data->mlx.mlx, p->name, &p->width,
					&p->height)))
			return (55 + p->id - 1);
		p->line = (unsigned int *)mlx_get_data_addr(p->img, &a, &p->size, &a);
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
			return (16 + id);
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

int		verif_color(char *sep)
{
	int		val;
	char	*tmp;

	sep = ft_strjoin(".;,", sep);
	tmp = ft_strtok(NULL, sep);
	free(sep);
	if (tmp == NULL)
		return (35 + 255);
	val = ft_atoi(tmp);
	if (val < 0 || 255 < val)
		return (40 + 255);
	return (val);
}

int		set_colors(t_file *file, char id, char *sep)
{
	int		val;
	int		*tmp;
	char	*verif;

	if (id == 6)
		tmp = &file->floor;
	else
		tmp = &file->ceiling;
	if (tmp[0])
		return (33);
	if ((val = verif_color(sep)) > 255)
		return (val - 255 + id - 6);
	*tmp = (val << 16);
	printf("color : %d = %d\t", val, *tmp);
	if ((val = verif_color(sep)) > 255)
		return (val - 255 + id);
	*tmp |= val << 8;
	printf("%d = %d\t", val, *tmp);
	if ((val = verif_color(sep)) > 255)
		return (val - 255 + id);
	*tmp |= val;
	printf("%d = %d\t", val, *tmp);
	verif = ft_strtok(NULL, sep);
	if (verif != NULL)
		return (37 + id);
	return (0);
}
