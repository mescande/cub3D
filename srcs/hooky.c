/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooky.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:12:57 by user42            #+#    #+#             */
/*   Updated: 2021/01/20 20:02:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		focus_out(int key, t_gnrl *data)
{
	(void)key;
	data->player.mov[X] = 0;
	data->player.mov[Y] = 0;
	data->player.rot[X] = 0;
	data->player.rot[Y] = 0;
	data->player.tran[X] = 0;
	data->player.tran[Y] = 0;
	return (0);
}

int		focus_in(int key, t_gnrl *data)
{
	(void)key;
	data->player.reload = 1;
	return (0);
}
