/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:21:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 20:14:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define X 0
# define Y 1

enum	e_textures {
	T_NO,
	T_SO,
	T_WE,
	T_EA,
	T_S,
};

typedef struct	s_wall_textures {
	char					*name;
	int						id;
	struct s_wall_textures	*next;
}				t_tex;

typedef struct	s_map {
	char	**map;
	int		height;
	int		lenght;
}				t_map;

typedef struct	s_file_information {
	char	res[2];
	t_map	map;
	t_tex	*textures;
	char	ceiling[3];
	char	floor[3];
}				t_file;

typedef struct	s_mlx_informations {
	void	*mlx;
	void	*win;
	void	*img;
}				t_mlx;

typedef struct	s_general_informations {
	t_file	file;
	t_mlx	mlx;
}				t_gnrl;

int				args_management(int ac, char **av);

/*
**		Parsing main function
*/
int				verif_file_extension(char *name);
char			*vlen(char *str, char *type);
int				parsit(t_file *file, char *name);

int				set_resolution(t_file *file);
int				set_textures(t_file *file, char id);
int				set_colors(t_file *file, char id);

int				map_verif();
int				map_parse(char *line, t_file *file);

/*
**		error manager and free gestion
*/
int				ft_close(int fd, int ret, char *line);
int				ft_puterror(int i);
int				ft_freeemee(t_gnrl *info, int i);

/*
**		MLX managing (start, close, free...)
*/
int				start_mlx(t_gnrl *info);
void			end_mlx(t_mlx win);


#endif
