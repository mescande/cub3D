/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 00:04:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 12:57:06 by user42           ###   ########.fr       */
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

/*
**	NO,	SO,	WE,	EA,	S
**	0	1	2	3	4
*/
int		set_textures(t_file *file, int id)
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
	if (!(new = (t_tex *)malloc(sizeof(t_tex))))
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
	return (0);
}
