/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:20:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 20:14:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	select_id(char *id)
{
	if (id[0] == 'N')
		return (T_NO);
	if (id[0] == 'S')
	{
		if (id[1] == 'O')
			return (T_SO);
		return (T_S);
	}
	if (id[0] == 'E')
		return (T_EA);
	return (T_WE);
}

int		assign(char *id, t_file *file)
{
	static int	map = 0;

	if (map)
		return (-1);
	if (id == NULL)
		return (0);
	if (!ft_strcmp(id, "R"))
		return (set_resolution(file));
	if (!ft_strcmp(id, "NO") || !ft_strcmp(id, "SO") || !ft_strcmp(id, "EA")
			|| !ft_strcmp(id, "WE") || !ft_strcmp(id, "S"))
		return (set_textures(file, select_id(id)));
	if (!ft_strcmp(id, "F"))
		return (set_colors(file, 0));
	if (!ft_strcmp(id, "C"))
		return (set_colors(file, 1));
	if (ft_strnstr(id, "11", 2))
	{
		map = 1;
		return (-1);
	}
	printf("|%s|\n", id);
	return (11);
}

int		verif_file_extension(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (name[len - 4] != '.' || name[len - 3] != 'c' || name[len - 2] != 'u'
			|| name[len - 1] != 'b')
		return (1);
	return (0);
}

int		parsit(t_file *file, char *name)
{
	int		fd;
	char	*line;
	int		gnl;

	if ((fd = open(name, O_RDONLY)) == -1)
		return (1);
	if (verif_file_extension(name))
		return (2);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl == -1)
			return (ft_close(fd, 5, line));
		if ((gnl = assign(ft_strtok(line, " \t"), file)) > 0)
			return (ft_close(fd, gnl, line));
		if (gnl == -1)
		{
			if ((gnl = map_parse(line, file)))
				return (ft_close(fd, gnl, line));
		}
		else
			free(line);
	}
	if ((gnl = map_verif()))
		return (gnl);
	return (ft_close(fd, 0, line));
}
