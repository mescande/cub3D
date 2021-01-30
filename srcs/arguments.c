/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 23:33:25 by user42            #+#    #+#             */
/*   Updated: 2021/01/30 13:07:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	args[] = "Arguments :\n\
	fichier		un fichier .cub formatte comme indique dans le sujet\n\
	--save		commande du sujet, permet de prendre un screenshot en .bmp\n\
	-h ou --help	affiche cette aide\n\
	-smart		laisse plus de libertees a certaines fonctions\n\
	-fov=<value>	definie une valeur precise pour le fov\n\
	-speed=<value	definie une valeur precise pour la vitesse\n";

static void	help(t_gnrl *data)
{
	data->help = ON;
	printf("%sCube3D%s par %smescande%s (2020 Jan)\n\n", BOLDWHITE, RESET,
			BLUE, RESET);
	ft_printf("utilisation : ./Cub3D [args/fichier]\n\n");
	ft_printf("%s", args);
	ft_printf("\nAllez voir le sujet dont voici le lien si vous avez plus\
d'interrogations :\nhttps://cdn.intra.42.fr/pdf/pdf/17283/en.subject.pdf\n");
}

static void usage(t_gnrl *data)
{
	data->help = ON;
	printf("%sUSAGE :%s\t./Cub3D [args/fichiers]\n", BOLDWHITE, RESET);
	printf("Executez ./Cub3D --help pour plus d'informations\n");
}

static void	save(t_gnrl *data)
{
	if (strcmp(data->av[data->ac], "--save"))
		invalid(data);
	data->save = ON;
	if (data->av[data->ac + 1] && !ft_strcmp(data->av[data->ac + 1]
				+ ft_strlen(data->av[data->ac + 1]) - 4, ".bmp"))
		data->dest = data->av[data->ac++ + 1];
	else
		data->dest = "screenshot.bmp";
}

static void	smart(t_gnrl *data)
{
	if (strcmp(data->av[data->ac], "-smart"))
		invalid(data);
	data->is_smart = ON;
}

void	file_name(t_gnrl *data)
{
	data->file.ac = data->ac;
}

static t_args	list[] = {
	{"--save", save},
	{"-h", help},
	{"--help", help},
	{"-help", help},
	{"-smart", smart},
	{".cub", file_name},
	{NULL, 0}
};

void	invalid(t_gnrl *data)
{
	printf("Argument invalide, faites --help pour plus de precision\n");
	data->help = ON;
	data->ac = -1;
}

int		args_management(int ac, char **av, t_gnrl *data)
{
	int		res;
	int 	i;

	res = 1;
	if (ac == 1)
	{
		usage(data);
		return (0);
	}
	data->ac = 1;
	data->av = av;
	while (data->ac < ac && data->ac)
	{
		i = 0;
		while (list[i].arg && !ft_strstr(av[data->ac], list[i].arg))
			i++;
		if (!list[i].arg)
			invalid(data);
		else
			list[i].fct(data);
		data->ac++;
	}
	if (data->help)
		res = 0;
	return (res);
}
