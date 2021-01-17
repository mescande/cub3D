/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:21:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 20:37:14 by user42           ###   ########.fr       */
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

typedef struct	s_wall_textures {
	char					*name;
	int						id;
	unsigned int			color;
	struct s_wall_textures	*next;
}				t_tex;

typedef struct	s_map {
	char	**map;
	int		height;
	int		length;
	int		start[2];
	char	dir;
}				t_map;

typedef struct	s_file_information {
	int		res[2];
	t_map	map;
	t_tex	*textures;
	int		ceiling;
	int		floor;
}				t_file;

typedef struct	s_mlx_informations {
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*line;
	int				size;
}				t_mlx;

typedef struct	s_player_informations {
	double	pos[2];
	double	dir[2];
	double	plane[2];
	int		posi[2];
	int		life;
	int		rot;
	int		mov;
	char	**map;
}				t_play;

typedef struct	s_general_informations {
	t_file	file;
	t_mlx	mlx;
	t_play	player;
	double	fov;
	int		is_smart;
	int		quit;
}				t_gnrl;

struct			s_parse_assign_fonction {
	char	*id;
	int		(*fct)(t_file *file, char id, char *sep);
};

typedef struct	s_ray_informations {
	int		gap[2];
	double	*i;
	int		pos[2];
	double	ray[2];
	double	start[2];
	double	side[2];
	double	delta[2];
	double	ratio;
	t_play	*player;
	int		wall;
	double	dist;
	t_map	*map;
}				t_ray;

/*
**		Argument management
*/
int				args_management(int ac, char **av, t_gnrl *data);

/*
**		Parsing functions
*/
int				verif_file_extension(char *name);
char			*vlen(char *str, char *type);
int				parsit(t_file *file, char *name);

int				set_resolution(t_file *file, char id, char *sep);
int				set_textures(t_file *file, char id, char *sep);
int				set_colors(t_file *file, char id, char *sep);

int				map_verif(t_file *file);
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
void			end_mlx(t_mlx *win);

int				key_release(int key, t_gnrl *data);
int				key_press(int key, t_gnrl *data);
int				c3d_loop(t_gnrl *data);

int				rotate(t_gnrl *data);
int				movement(t_gnrl *data);
void			map_cpy(char **dst, t_map src);
int				player_manage(t_gnrl *data);

int				show_map(t_gnrl *data);
int				put_square(int x, int y, t_gnrl *data);
int				calcul_img(t_gnrl *data);

/*
**		Math fonctions
*/
double			*add_2d(double *t1, double *t2);
double			*sub_2d(double *t1, double *t2);
double			*mul_2d(double *t1, double val);

double			abs_d(double i);

#endif
