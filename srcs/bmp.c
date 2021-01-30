/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:15:48 by user42            #+#    #+#             */
/*   Updated: 2021/01/30 13:52:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bmp.h"

static int	write_image(t_gnrl *data, int fd, t_bmp *h)
{
	int				i;
	int				j;
	char		 	*line;
	unsigned int	*img;

	if (!(img  = (unsigned int *)ft_memalloc(sizeof(int) * h->width * h->height))
			|| !(line  = (char *)ft_memalloc(sizeof(char) * 3 * h->width * h->height)))
		return (4);
//	if (!(data->mlx.mlx = mlx_init()))
//		return (7);
	data->mlx.line = img;
	data->mlx.size = h->width;
	printf("%p\t%p\n\n", line, data->mlx.line);
	if ((j = start_mlx(data))
			|| (j = calcul_img(data)))
		return (j);
	j = 0;
	while (j < data->file.res[Y])
	{
		i = 0;
		while (i < data->file.res[X])
		{
			line[(j * h->width + i) * 3 + 0] = (char)(img[(h->height - j - 1)
					* h->width + i]);
			line[(j * h->width + i) * 3 + 1] = (char)(img[(h->height - j - 1)
					* h->width + i] >> 8);
			line[(j * h->width + i) * 3 + 2] = (char)(img[(h->height - j - 1)
					* h->width + i] >> 16);
			i++;
		}
		j++;
	}
	write(fd, line, 3 * h->width * h->height - 2);
	free(img);
	free(line);
	return (0);
}

static void	init_header(t_gnrl *data, t_bmp *h)
{
	ft_bzero(h, sizeof(t_bmp));
	h->bmpsignature[0] = 'B';
	h->bmpsignature[1] = 'M';
	h->sizeof_file = sizeof(t_bmp) + data->file.res[X] * data->file.res[Y] * 3;
	h->sizeof_thisheader = 40;
	h->width = data->file.res[X];
	h->height = data->file.res[Y];
	h->numberofcolorplanes = 1;
	h->colordepth = 24;
}

int		screen_it(t_gnrl *data)
{
	t_bmp	header;
	int		fd;

	fd = open(data->dest, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	init_header(data, &header);
	write(fd, &header, sizeof(t_bmp));
	write_image(data, fd, &header);
	close(fd);
	return (0);
}
