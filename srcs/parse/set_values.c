/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 00:04:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/30 15:14:52 by user42           ###   ########.fr       */
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
	if (tmp == NULL || file->res[X] <= 0)
		return (12);
	file->res[Y] = ft_atoi(tmp);
	tmp = ft_strtok(NULL, sep);
	if (tmp != NULL || file->res[Y] <= 0)
		return (13);
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
	if ((val = verif_color(sep)) > 255)
		return (val - 255 + id);
	*tmp |= val << 8;
	if ((val = verif_color(sep)) > 255)
		return (val - 255 + id);
	*tmp |= val;
	verif = ft_strtok(NULL, sep);
	if (verif != NULL)
		return (37 + id);
	return (0);
}
