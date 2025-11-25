/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:17:05 by danz              #+#    #+#             */
/*   Updated: 2025/11/25 19:02:09 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	put_pixel(int x, int y, int color, t_fdf fdf)
{
	int	pos;

	if (x >= IMG_WID || y >= IMG_HGT || x < 0 || y < 0)
		return ;
	pos = fdf.size_line * y + x * (fdf.bpp / 8);
	*(unsigned int *)(fdf.addr + pos) = color;
}

int	color_calc(int color0, int color1, float ratio)
{
	int	rgb0[3];
	int	rgb1[3];
	int	rgbret[3];

	rgb0[0] = (color0 >> 16) & 0xFF;
	rgb0[1] = (color0 >> 8) & 0xFF;
	rgb0[2] = color0 & 0xFF;
	rgb1[0] = (color1 >> 16) & 0xFF;
	rgb1[1] = (color1 >> 8) & 0xFF;
	rgb1[2] = color1 & 0xFF;
	rgbret[0] = rgb0[0] + (rgb1[0] - rgb0[0]) * ratio;
	rgbret[1] = rgb0[1] + (rgb1[1] - rgb0[1]) * ratio;
	rgbret[2] = rgb0[2] + (rgb1[2] - rgb0[2]) * ratio;
	return ((rgbret[0] << 16) | (rgbret[1] << 8) | rgbret[2]);
}

int	lerp(t_point p0, t_point p1, int pos[2])
{
	float	ratio;
	float	dist;
	int		rel[2];

	rel[0] = abs(p1.osd[0] - p0.osd[0]);
	rel[1] = abs(p1.osd[1] - p0.osd[1]);
	dist = sqrtf(pow(rel[0], 2) + pow(rel[1], 2));
	if (dist == 0)
		return (p0.color);
	ratio = sqrtf(pow(pos[0] - p0.osd[0], 2) + pow(pos[1] - p0.osd[1], 2))
		/ dist;
	if (ratio > 1.0)
		ratio = 1.0;
	if (ratio < 0.0)
		ratio = 0.0;
	return (color_calc(p0.color, p1.color, ratio));
}
