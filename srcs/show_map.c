/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:42:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/17 12:31:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int put_square(int x, int y, char val, t_gnrl *data)
{
	int	color;
	int	i;
	int j;

	if (val == '1')
		color = 0x0000ff;
	else if (val == 'N')
		color = 0xffffff;
	else
		color = 0x009900;
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			data->mlx.line[(x * 10 + i) * data->mlx.size + (y * 10) + j] = color;
	}
	return (0);
}
