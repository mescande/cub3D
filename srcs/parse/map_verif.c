/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:29:02 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 20:18:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_verif()
{
	return (0);
}

int		map_parse(char *line, t_file *file)
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
	file->map.map[index++] = line;
	file->map.height++;
	if ((len = ft_strlen(line)) > file->map.lenght)
		file->map.lenght = len;
	return (0);
}
