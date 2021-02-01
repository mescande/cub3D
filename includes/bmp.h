/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:48:04 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 11:53:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <stdint.h>

typedef struct __attribute__((__packed__))	s_bitmap_24 {
	char		bmpsignature[2];
	uint32_t	sizeof_file;
	uint32_t	reserved;
	uint32_t	pixeloffset;
	uint32_t	sizeof_thisheader;
	int32_t		width;
	int32_t		height;
	uint16_t	numberofcolorplanes;
	uint16_t	colordepth;
	uint32_t	compressionmethod;
	uint32_t	rawbmpdatasize;
	int32_t		horizontalres;
	int32_t		verticalres;
	uint32_t	colortablentries;
	uint32_t	importantcolors;
}				t_bmp;

#endif
