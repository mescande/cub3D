/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_smart.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:15:50 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 19:36:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_smart(t_file *file)
{
	if (file->floor == -1)
		file->floor = 0x50b940;
	if (file->ceiling == -1)
		file->ceiling = 0x5040b9;
	if (!file->res[X])
		file->res[X] = 1024;
	if (!file->res[Y])
		file->res[Y] = 1024;
}
