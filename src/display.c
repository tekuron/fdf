/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:40:21 by danz              #+#    #+#             */
/*   Updated: 2025/11/22 01:47:35 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "limits.h"
#include "mlx.h"

void	put_pixels(t_fdf fdf)
{
	t_list	*cur;
	t_point	*point;

	if (!fdf.addr || !fdf.coords)
		return ;
	cur = fdf.coords;
	while (cur)
	{
		point = cur->content;
		if (point->osd[0] >= 0 && point->osd[0] < IMG_WID
			&& point->osd[1] >= 0 && point->osd[1] < IMG_HGT)
		{
			put_pixel(point->osd[0], point->osd[1], point->color, fdf);
		}
		cur = cur->next;
	}
}

static t_matrix	*create_transformation_matrix(t_fdf *fdf)
{
	t_matrix	*scale;
	t_matrix	*rotation;
	t_matrix	*translation;
	t_matrix	*transform;
	t_matrix	*result;

	scale = matrix_scale(fdf->scale, fdf->scale, fdf->scale);
	rotation = matrix_rotation_full(fdf->rotation_x, fdf->rotation_y, fdf->rotation_z);
	translation = matrix_translation(fdf->offset_x, fdf->offset_y, 0.0f);
	if (!scale || !rotation || !translation)
		return (NULL);
	transform = matrix_product(scale, rotation);
	if (!transform)
		return (NULL);
	result = matrix_product(transform, translation);
	free_matrix(transform);
	free_matrix(scale);
	free_matrix(rotation);
	free_matrix(translation);
	return (result);
}

static t_matrix	*get_projection_matrix(int projection_type)
{
	if (projection_type == PERSPECTIVE)
		return (matrix_perspective_projection());
	else
		return (matrix_isometric_projection());
}

static void	apply_matrix_to_points(t_list *coords, t_matrix *final_transform)
{
	t_list	*cur;
	t_point	*point;

	cur = coords;
	while (cur)
	{
		point = cur->content;
		if (point->iso_coords)
			free_matrix(point->iso_coords);
		point->iso_coords = matrix_product(point->coords, final_transform);
		cur = cur->next;
	}
}

void	apply_transformations(t_fdf *fdf)
{
	t_matrix	*transform;
	t_matrix	*projection;
	t_matrix	*final_transform;

	transform = create_transformation_matrix(fdf);
	projection = get_projection_matrix(fdf->projection_type);
	if (!transform || !projection)
		return ;
	final_transform = matrix_product(transform, projection);
	if (!final_transform)
		return ;
	apply_matrix_to_points(fdf->coords, final_transform);
	free_matrix(transform);
	free_matrix(projection);
	free_matrix(final_transform);
}
