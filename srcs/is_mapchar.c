/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_mapchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:17:05 by user42            #+#    #+#             */
/*   Updated: 2021/01/21 00:41:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		is_sprite(char c)
{
	return (c == '2');
}

int		is_wall(char c)
{
	if (c == '1')
		return (1);
	return (0);
}

int		is_stop(char c)
{
	return (is_wall(c) || is_sprite(c));
}

int			is_player_position(char c)
{
	if (c == 'n' || c == 's' || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W'
			|| c == 'e' || c == 'w')
		return (1);
	return (0);
}
