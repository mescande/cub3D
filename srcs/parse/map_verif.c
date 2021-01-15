/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:29:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/16 00:04:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			map_squarer(t_map *map)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->map[i]);
		if (!(res = /*ft_me*/malloc(map->length + 2)))
			return (0);
		res[0] = ' ';
		ft_memcpy(res + 1, map->map[i], len);
		ft_memset(res + len + 1, ' ', ((long)(map->length + 2 - len)));
		free(map->map[i]);
		map->map[i] = res;
		i++;
	}
	return (0);
}

int			map_verif_char(int i, int j, t_map map_d, char **map, int *pos)
{
	if (map[i][j] == '0' || map[i][j] == '2')
	{
		if (i == 0 || i == map_d.height || j == 1 || j == map_d.length)
			return (47);
		if (	   map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' '
				|| map[i - 1][j + 1] == ' ' || map[i][j - 1] == ' '
				|| map[i][j + 1] == ' ' || map[i + 1][j - 1] == ' '
				|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')
		{
/*		printf("map[%d][%d] = %c\nmap[%d] = |%s|\n", i, j, map[i][j], i, map[i]);
		printf("%c%c%c\n%c%c%c\n%c%c%c\n", map[i - 1][j - 1], map[i - 1][j], map[i - 1][j + 1], map[i][j - 1], 'H', map[i][j + 1], map[i + 1][j - 1], map[i + 1][j], map[i + 1][j + 1]);
		printf("%s\n", map[i + 1]);
*/			return (46);
		}
	}
	else if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
			|| map[i][j] == 'W')
	{
		if ((*pos)++)
			return (45);
	}
	else if (map[i][j] != '1' && map[i][j] != ' ')
	{
		return (48);
	}
	return (0);
}

int			map_verif(t_file *file)
{
	int		ret;
	int		i;
	int		j;
	int		pos;

	i = -1;
	pos = 0;
	if ((ret = map_squarer(&file->map)))
		return (ret);
	while (++i < file->map.height)
	{
		ft_printf("|%s|\n", file->map.map[i]);
		j = 0;
		while (++j < file->map.length + 1)
		{
			if ((ret = map_verif_char(i, j, file->map, file->map.map, &pos)))
				return (ret);
		}
	}
	if (pos == 0)
		return (44);
	return (0);
}

int			map_parse(char *line, t_file *file)
{
	static int	index = 0;
	int			len;

	if (!strcmp(line, ""))
	{
		index = -1;
		return (0);
	}
	if (index == -1)
		return (43);
	if (index == 0 && (!(file->map.map =
					(char **)ft_memalloc(100 * sizeof(char *)))))
		return (4);
	else if (index % 100 == 0)
		if (!(file->map.map = (char **)ft_memrealloc(file->map.map, (index
							+ 100) * sizeof(char *), index * sizeof(char *))))
			return (4);
	file->map.map[index++] = ft_strdup(line);
	file->map.height++;
	if ((len = ft_strlen(line)) > file->map.length)
		file->map.length = len;
	return (0);
}
