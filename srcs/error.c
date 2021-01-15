/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescande <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:36:20 by mescande          #+#    #+#             */
/*   Updated: 2021/01/15 23:44:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*line_interpret(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\\' && line[i + 1] == 'n')
		{
			line[i] = '\n';
			ft_memmove(line + i + 1, line + i + 2, ft_strlen(line + i + 2) + 1);
		}
		if (line[i] == '\\' && line[i + 1] == 't')
		{
			line[i] = '\t';
			ft_memmove(line + i + 1, line + i + 2, ft_strlen(line + i + 2) + 1);
		}
	}
	return (line);
}

int			ft_close(int fd, int ret, char *line)
{
	close(fd);
	if (line)
		free(line);
	return (ret);
}

int			ft_puterror(int i)
{
	int		fd;
	char	*line;
	int		gnl;
	int		k;

	k = 1;
	if ((fd = open("srcs/error", O_RDONLY)) == -1)
		return ((write(2, "open is broken, fix your computer...\n", 37)) == 37);
	while ((gnl = get_next_line(fd, &line)) && i)
	{
		if (gnl == -1 || i == 3)
		{
			gnl = write(2, "Error 3 : GNL status -1; cf -gnlhelp\n", 27);
			return (ft_close(fd, 5, line));
		}
		if (i - k == 0)
		{
			ft_fprintf(2, "\nError %d\n\t%s\n", i, line_interpret(line));
			return (ft_close(fd, i, line));
		}
		free(line);
		k++;
	}
	return (ft_close(fd, i, line));
}

int			ft_freeemee(t_gnrl *data, int i)
{
	void	*p1;
	int		l;

	l = -1;
	while (data->file.textures)
	{
		p1 = data->file.textures;
		free(data->file.textures->name);
		data->file.textures = data->file.textures->next;
		free(p1);
	}
	while (++l < data->file.map.height)
	{
		free(data->file.map.map[l]);
	}
	if (data->file.map.map)
		free(data->file.map.map);
	if (data->mlx.mlx || data->mlx.win)
		end_mlx(data->mlx);
	return ((i == 0 ? 0 : ft_puterror(i)));
}
