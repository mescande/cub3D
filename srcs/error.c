/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescande <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:36:20 by mescande          #+#    #+#             */
/*   Updated: 2021/01/20 13:45:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*errors[] = {
	"Undefined error, something went really wrong",
	"file error; Can't find the file or the file cannot be read\n\
		Check if the path is ok.",
	"file error; Your file is not a .cub file.",
	"Allocation error, Malloc went wrong",
	"GNL status -1; cf -gnlhelp",
	"USAGE :\n\t./cub3D FILE (arg)\n\tUse -h for more help",
	"mlx_init() failed to set up a connection to the X server",
	"mlx_get_screen_size() returned 0",
	"mlx_new_window() failed to create a new window",
	"mlx_get_data_addr() didn't return 4 bits per pixel",
	"parsing; Unknown identifier",
	"parsing; Resolution has not enough arguments",
	"parsing; Resolution has to many arguments",
	"parsing; Resolution is defined twice",
	"",
	"parsing; Texture for NO is defined twice",
	"parsing; Texture for SO is defined twice",
	"parsing; Texture for WE is defined twice",
	"parsing; Texture for EA is defined twice",
	"parsing; Texture for S is defined twice",
	"",
	"parsing; Texture for NO is not specified",
	"parsing; Texture for SO is not specified",
	"parsing; Texture for WE is not specified",
	"parsing; Texture for EA is not specified",
	"parsing; Texture for S is not specified",
	"",
	"parsing; Texture for NO has too many arguments",
	"parsing; Texture for SO has too many arguments",
	"parsing; Texture for WE has too many arguments",
	"parsing; Texture for EA has too many arguments",
	"parsing; Texture for S has too many arguments",
	"parsing; Floor is defined twice",
	"parsing; Ceiling is defined twice",
	"parsing; Floor color has not enough arguments",
	"parsing; Ceiling color has not enough arguments",
	"parsing; Floor color has too many arguments",
	"parsing; Ceiling color has too many arguments",
	"",
	"parsing; Floor color out of range",
	"parsing; Ceiling color out of range",
	"",
	"Map; Empty line in your map or element after the map.",
	"Map; No player position defined",
	"Map; To many player position defined",
	"Map; Invalid map -spaces in the middle",
	"Map; Invalid map -Wall missing",
	"Map; Invalid map -Unknown character",
	"",
	"Texture; File type for NO is not managed",
	"Texture; File type for SO is not managed",
	"Texture; File type for WE is not managed",
	"Texture; File type for EA is not managed",
	"Texture; File type for S is not managed",
	"Texture; File for NO couldn't been read",
	"Texture; File for SO couldn't been read",
	"Texture; File for WE couldn't been read",
	"Texture; File for EA couldn't been read",
	"Texture; File for S couldn't been read",
	""
};

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
	int		k;

	k = 0;
	while (errors[k])
	{
		if (i - k == 1)
		{
			ft_fprintf(2, "\nError %d\n\t%s\n", i, line_interpret(errors[k]));
			return (i);
		}
		k++;
	}
	return (i);
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
		if (data->file.textures->img)
			mlx_destroy_image(data->mlx.mlx, data->file.textures->img);
		data->file.textures = data->file.textures->next;
		free(p1);
	}
	while (++l < data->file.map.height)
	{
		if (data->player.map[l])
			free(data->player.map[l]);
		free(data->file.map.map[l]);
	}
	if (data->file.map.map)
		free(data->file.map.map);
	if (data->player.map)
		free(data->player.map);
	end_mlx(&data->mlx);
	return ((i == 0 ? 0 : ft_puterror(i)));
}
