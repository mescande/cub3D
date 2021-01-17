/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooky.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:12:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 15:01:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		rotate(t_gnrl *data)
{
	double	save;
	double	cv;
	double	sv;

	cv = cos(0.1 * data->player.rot);
	sv = sin(0.1 * data->player.rot);
	save = data->player.dir[X];
	data->player.dir[X] = data->player.dir[X] * cv + data->player.dir[Y] * sv;
	data->player.dir[Y] = data->player.dir[Y] * cv + save * sv;
	save = data->player.plane[X];
	data->player.plane[X] = data->player.plane[X] * cv +
		data->player.plane[Y] * sv;
	data->player.dir[Y] = data->player.plane[Y] * cv + save * sv;
	return (1);
}
