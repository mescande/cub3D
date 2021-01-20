/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 23:33:25 by user42            #+#    #+#             */
/*   Updated: 2021/01/20 13:48:37 by user42           ###   ########.fr       */
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

int		args_management(int ac, char **av, t_gnrl *data)
{
	int		res;

	res = 0;
	if (ac == 1)
	{
		usage(data);
		return (res);
	}
	data->fov = 66;
	while (ac-- > 1)
	{
		if (!ft_strcmp(av[ac], "--save"))
			data->save = ON;
		else if (!ft_strcmp(av[ac], "-h") || !ft_strcmp(av[ac], "--help")
				|| !ft_strcmp(av[ac], "-help"))
			help(data);
		else if (!ft_strcmp(av[ac], "-smart"))
			data->is_smart = ON;
		else if (ft_strstr(av[ac], "-fov="))
			data->fov = ft_atoi(av[ac] + 5);
		else if (ft_strstr(av[ac], ".cub"))
			res = ac;
	}
	if (res == 0)
		usage(data);
	if (data->help)
		res = 0;
	return (res);
}
