/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:20:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 12:59:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		select_id(char *id)
{
	if (id[0] == 'N')
		return (T_NO);
	if (id[0] == 'S')
	{
		if (id[1] == 'O')
			return (T_SO);
		return (T_S);
	}
	if (id[0] = 'E')
		return (T_EA);
	return (T_WE);
}

int		assign(char *id, t_file *file)
{
	(void)line;
	(void)file;
	if (!ft_strcmp(id, "R"))
		return (set_resolution(file));
	if (!ft_strcmp(id, "NO") || !ft_strcmp(id, "SO") || !ft_strcmp(id, "EA")
			|| !ft_strcmp(id, "WE") || !ft_strcmp(id, "S"))
		return (set texture(file, selectid(id)));
	if (!ft_strcmp(id, "F"))
		return (set_color(file, 
	if (!ft_strcmp(id, "C"))
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
		if (!ft_strcmp(line, ""))
			;
		else if ((gnl = assign(ft_strtok(line, " \t"), file)) != 0)
			return (ft_close(fd, gnl, line));
		free(line);
	}
	return (ft_close(fd, 0, line));
}
