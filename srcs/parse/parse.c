/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:20:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 11:00:13 by user42           ###   ########.fr       */
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

int		assign(char *line, t_file *file, t_gnrl *data)
{
	static int	map = 0;
	int			i;
	char		*id;
	char		*save;
	const char	*sep = (data->is_smart == 0 ? " \t\r\n\v\f" : " \t");

	i = -1;
	if (map)
		return (-1);
	save = ft_strdup(line);
	file->comma = ft_strcount(line, ',') + ft_strcount(line, ';');
	if (data->is_smart)
		file->comma = 2;
	id = ft_strtok(save, sep);
	if (id == NULL)
		return (free_n_ret(save, 0));
	while (dest[++i].id)
		if (!ft_strcmp(dest[i].id, id))
			return (free_n_ret(save, dest[i].fct(file, i, (char *)sep)));
	if (ft_strnstr(id, "11", ft_strlen(id)))
		return (free_n_ret(save, -1 + ((map = 1) == 0)));
	free(save);
	return (11);
}

int		parsit(t_file *file, char *name, t_gnrl *data)
{
	int		fd;
	char	*line;
	int		gnl;

	line = NULL;
	if (ft_strcmp(name + ft_strlen(name) - 4, ".cub"))
		return (3);
	if ((fd = open(name, O_RDONLY)) == -1)
		return (2);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl == -1)
			return (ft_close(fd, 5, NULL));
		if ((gnl = assign(line, file, data)) > 0)
			return (ft_close(fd, gnl, line));
		if (gnl == -1)
		{
			if ((gnl = map_parse(line, file)))
				return (ft_close(fd, gnl, line));
		}
		free(line);
	}
	if ((gnl = map_verif(file, data)))
		return (ft_close(fd, gnl, line));
	return (ft_close(fd, 0, line));
}
