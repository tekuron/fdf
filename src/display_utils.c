/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:47:40 by danz              #+#    #+#             */
/*   Updated: 2025/11/26 12:49:08 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "limits.h"
#include "mlx.h"

static void	change(int range_x[2], int range_y[2], int x, int y)
{
	if ((int)x < range_x[0])
		range_x[0] = (int)x;
	if ((int)x > range_x[1])
		range_x[1] = (int)x;
	if ((int)y < range_y[0])
		range_y[0] = (int)y;
	if ((int)y > range_y[1])
		range_y[1] = (int)y;
}

static void	get_ranges(t_list *coords, int range_x[2], int range_y[2])
{
	t_point	*point;
	float	x;
	float	y;

	range_x[0] = INT_MAX;
	range_x[1] = INT_MIN;
	range_y[0] = INT_MAX;
	range_y[1] = INT_MIN;
	while (coords)
	{
		point = coords->content;
		if (!point || !point->iso_coords)
		{
			coords = coords->next;
			continue ;
		}
		x = point->iso_coords->matrix[0][0];
		y = point->iso_coords->matrix[1][0];
		change(range_x, range_y, x, y);
		coords = coords->next;
	}
	if (range_x[0] == range_x[1])
		range_x[1]++;
	if (range_y[0] == range_y[1])
		range_y[1]++;
}

static float	calculate_scale(int range_x[2], int range_y[2])
{
	float	scale_x;
	float	scale_y;

	scale_x = (IMG_WID * 0.8f) / (range_x[1] - range_x[0]);
	scale_y = (IMG_HGT * 0.8f) / (range_y[1] - range_y[0]);
	if (scale_x <= scale_y)
		return (scale_x);
	return (scale_y);
}

static void	apply_scale_offset(t_list *coords, int range_x[2],
	int range_y[2], float scale)
{
	t_point	*point;
	int		offset[2];

	offset[0] = (IMG_WID - (range_x[1] - range_x[0]) * scale) / 2;
	offset[1] = (IMG_HGT - (range_y[1] - range_y[0]) * scale) / 2;
	while (coords)
	{
		point = (t_point *)coords->content;
		if (!point || !point->iso_coords)
		{
			coords = coords->next;
			continue ;
		}
		point->osd[0] = (int)((point->iso_coords->matrix[0][0]
					- range_x[0]) * scale) + offset[0];
		point->osd[1] = (int)((point->iso_coords->matrix[1][0]
					- range_y[0]) * scale) + offset[1];
		coords = coords->next;
	}
}

void	save_osd(t_fdf *fdf)
{
	t_list			*coords;
	t_point			*cur;
	int				range_x[2];
	int				range_y[2];
	static float	scale;

	coords = fdf->coords;
	get_ranges(coords, range_x, range_y);
	if (!scale)
		scale = calculate_scale(range_x, range_y);
	apply_scale_offset(coords, range_x, range_y, scale);
	while (coords)
	{
		cur = coords->content;
		cur->osd[0] -= (IMG_WID / 2.0f) - ((IMG_WID / 2.0f) / fdf->scale);
		cur->osd[1] -= (IMG_HGT / 2.0f) - ((IMG_HGT / 2.0f) / fdf->scale);
		cur->osd[0] += fdf->offset_x;
		cur->osd[1] += fdf->offset_y;
		cur->osd[0] *= fdf->scale;
		cur->osd[1] *= fdf->scale;
		coords = coords->next;
	}
}
