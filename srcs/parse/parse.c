/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:20:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/16 16:12:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static struct s_parse_assign_fonction	dest[] = {
	{"R", set_resolution},
	{"NO", set_textures},
	{"SO", set_textures},
	{"WE", set_textures},
	{"EA", set_textures},
	{"S", set_textures},
	{"F", set_colors},
	{"C", set_colors},
	{NULL, 0}
};

int		assign(char *line, t_file *file)
{
	static int	map = 0;
	int			i;
	char		*id;
	char		*save;
	const char	*sep = /*(IS_SMART == 0 ? " \t\r\n\v\f" : */" \t"/*)*/;

	i = -1;
	if (map)
		return (-1);
	save = ft_strdup(line);
//	printf("Try with [%s]\n", save);
	id = ft_strtok(save, sep);
	if (id == NULL)
	{
		free(save);
		return (0);
	}
//	printf("Try with [%s]\n", id);
	while (dest[++i].id)
		if (!ft_strcmp(dest[i].id, id))
		{
			i = dest[i].fct(file, i, (char *)sep);
			free(save);
			return (i);
		}
	if (ft_strnstr(id, "11", ft_strlen(id)))
	{
		map = 1;
		free(save);
		return (-1);
	}
	printf("|%s|\n", id);
	free(save);
	return (11);
}

int		parsit(t_file *file, char *name)
{
	int		fd;
	char	*line;
	int		gnl;

	if (ft_strcmp(name + ft_strlen(name) - 4, ".cub"))
		return (3);
	if ((fd = open(name, O_RDONLY)) == -1)
		return (2);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl == -1)
			return (ft_close(fd, 5, line));
		if ((gnl = assign(line, file)) > 0)
			return (ft_close(fd, gnl, line));
		if (gnl == -1)
		{
			if ((gnl = map_parse(line, file)))
				return (ft_close(fd, gnl, line));
		}
		free(line);
	}
	if ((gnl = map_verif(file)))
		return (ft_close(fd, gnl, line));
	return (ft_close(fd, 0, line));
}
