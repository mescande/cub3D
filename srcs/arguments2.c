/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:24:29 by user42            #+#    #+#             */
/*   Updated: 2021/01/30 15:25:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	file_name(t_gnrl *data)
{
	data->file.ac = data->ac;
}

void	invalid(t_gnrl *data)
{
	printf("Argument invalide, faites --help pour plus de precision\n");
	data->help = ON;
	data->ac = -1;
}
