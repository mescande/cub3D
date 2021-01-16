/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 18:55:39 by user42            #+#    #+#             */
/*   Updated: 2021/01/16 19:34:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	*add_2d(double *t1, double *t2)
{
	t1[X] += t2[X];
	t1[Y] += t2[Y];
	return (t1);
}

double	*sub_2d(double *t1, double *t2)
{
	t1[X] -= t2[X];
	t1[Y] -= t2[Y];
	return (t1);
}

double	*mul_2d(double *t1, double val)
{
	t1[X] *= val;
	t1[Y] *= val;
	return (t1);
}
