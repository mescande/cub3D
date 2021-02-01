/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 21:15:48 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 19:32:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bmp.h"

static void	put_colors(char *line, unsigned int *img)
{
	line[0] = (char)(img[0]);
	line[1] = (char)(img[0] >> 8);
	line[2] = (char)(img[0] >> 16);
}

static int	write_image(t_gnrl *data, int fd, t_bmp *h)
{
	int				i;
	int				j;
	char			*line;
	unsigned int	*img;

	if (!(img = ft_memalloc(4 * data->file.res[X] * data->file.res[Y]))
	|| !(line = (char *)ft_memalloc(3 * data->file.res[X] * data->file.res[Y])))
		return (4);
	data->mlx.line = img;
	data->mlx.size = h->width;
	if ((j = calcul_img(data)))
		return (j);
	while (j < data->file.res[Y])
	{
		i = -1;
		while (++i < data->file.res[X])
			put_colors((line + (j * h->width + i) * 3),
					(img + (h->height - j - 1) * h->width + i));
		j++;
	}
	i = write(fd, line, 3 * h->width * h->height - 2);
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

int			screen_it(t_gnrl *data)
{
	t_bmp	header;
	int		fd;
	int		res;

	fd = open(data->dest, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (1);
	if ((res = start_mlx(data)))
		return (res);
	init_header(data, &header);
	res = write(fd, &header, sizeof(t_bmp));
	if (write_image(data, fd, &header))
		return (ft_close(fd, 4, NULL));
	(void)res;
	close(fd);
	return (0);
}
