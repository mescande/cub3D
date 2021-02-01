/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:21:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 23:34:53 by user42           ###   ########.fr       */
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
# include "keys.h"

# define X 0
# define Y 1
# define ON 1

typedef struct	s_wall_textures {
	char					*name;
	int						id;
	unsigned int			color;
	unsigned int			*line;
	int						size;
	void					*img;
	int						width;
	int						height;
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
	int		ac;
}				t_file;

typedef struct	s_mlx_informations {
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*line;
	int				size;
}				t_mlx;

typedef struct	s_sprite_list {
	int						id;
	int						pos[2];
	double					dist;
	int						column;
	struct s_sprite_list	*left;
	struct s_sprite_list	*right;
}				t_sprite;

typedef struct	s_player_informations {
	double		pos[2];
	double		dir[2];
	double		plane[2];
	double		*dists;
	char		life;
	char		rot[2];
	char		mov[2];
	char		tran[2];
	char		show_map;
	char		reload;
	char		**map;
	t_sprite	*tree;
}				t_play;

typedef struct	s_general_informations {
	t_file		file;
	t_mlx		mlx;
	t_play		player;
	double		fov;
	int			is_smart;
	int			quit;
	char		help;
	char		save;
	char		*dest;
	char		**av;
	int			ac;
	t_sprite	*sp;
	t_sprite	*cur_sp;
}				t_gnrl;

struct			s_parse_assign_fonction {
	char	*id;
	int		(*fct)(t_file *file, char id, char *sep);
};

typedef struct	s_args_assign_function {
	char	*arg;
	void	(*fct)(t_gnrl *data);
}				t_args;

typedef struct	s_ray_informations {
	int		gap[2];
	double	*i;
	int		pos[2];//position en int du rayon -> du mur trouve
	double	ray[2];//direction rayon
	double	start[2];//position joueur
	double	side[2];//longueur sur X/Y parcourue
	double	delta[2];//ecart entre 2 inter mur/rayon sur les axes X/Y
	double	ratio;//ratio colonne/largeur ecran
	t_play	*player;
	int		wall;//cote de case touche
	double	wallx;//distance relative entre le debut d'une case et le pt touche
	double	dist;//dist corrige parcouru par le rayon
	t_map	*map;
	int		h;
	double	tex[2];
	double	idet;//inverse determinant matrice joueur
}				t_ray;

/*
**		Argument management
*/
void			file_name(t_gnrl *data);
void			invalid(t_gnrl *data);
int				args_management(int ac, char **av, t_gnrl *data);

/*
**		Parsing functions
*/
int				verif_file_extension(char *name);
char			*vlen(char *str, char *type);
int				parsit(t_file *file, char *name, t_gnrl *data);

int				set_resolution(t_file *file, char id, char *sep);
int				open_texture(t_gnrl *data);
int				set_textures(t_file *file, char id, char *sep);
int				set_colors(t_file *file, char id, char *sep);

int				is_player_position(char c);
int				map_verif(t_file *file, t_gnrl *data);
int				map_parse(char *line, t_file *file);

int				is_sprite(char c);
int				is_wall(char c);
int				is_stop(char c);
int				is_player_position(char c);

/*
**		error manager and free gestion
*/
int				free_n_ret(void *p, int val);
int				ft_close(int fd, int ret, char *line);
int				ft_puterror(int i);
int				ft_freeemee(t_gnrl *info, int i);

/*
**		MLX managing (start, close, free...)
*/
int				start_mlx(t_gnrl *info);
void			end_mlx(t_mlx *win);

/*
**		Reaction fonctions to keybinds
*/
int				c3d_key(int key, t_gnrl *data, int press);
int				c3d_loop(t_gnrl *data);

int				focus_out(t_gnrl *data);
int				focus_in(t_gnrl *data);
int				key_release(int key, t_gnrl *data);
int				key_press(int key, t_gnrl *data);
int				expose(t_gnrl *data);

/*
**		Mouvement calcul
*/
int				rotate(t_gnrl *data);
int				translate(t_gnrl *data);
int				movement(t_gnrl *data);

void			map_cpy(char **dst, t_map src);
int				player_manage(t_gnrl *data);

/*
**		Rendering fonctions
*/
int				show_map(t_gnrl *data);

void			init_img(t_ray *r, t_gnrl *data);
void			init_ray(t_ray *r, t_gnrl *data, int i);
unsigned int	set_color(int id);
void			init_tex_values(t_ray *r, t_tex *tex);
void			react_map_char(t_ray *r, t_gnrl *data, int *stop);

void			set_side(t_ray *r);
int				calcul_img(t_gnrl *data);

void			show_textured(t_gnrl *data, t_sprite *s);
void			show_colored(t_gnrl *data, t_sprite *s);

void			init_show(int *size, t_gnrl *data, int *i, t_sprite *s);
void			sprite_sort(t_gnrl *data);
void			sprite_seen(t_gnrl *data, t_ray *r);
void			put_sprite(t_gnrl *data, t_sprite *s);

int				is_textured(int id, t_gnrl *data);
t_tex			*find_tex(int id, t_gnrl *data);

/*
**		Math fonctions
*/
double			*add_2d(double *t1, double *t2);
double			*sub_2d(double *t1, double *t2);
double			*mul_2d(double *t1, double val);

double			abs_d(double i);

/*
**		Screenshot
*/
int				screen_it(t_gnrl *data);

#endif
