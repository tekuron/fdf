/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:40:21 by danz              #+#    #+#             */
/*   Updated: 2025/11/25 23:44:16 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "limits.h"
#include "mlx.h"

static t_matrix	*get_projection_matrix(int projection_type)
{
	if (projection_type == PERSPECTIVE)
		return (matrix_cavalier_projection());
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
		point->iso_coords = matrix_product(final_transform, point->coords);
		cur = cur->next;
	}
}

void	apply_transformations(t_fdf *fdf)
{
	t_matrix	*transform;
	t_matrix	*projection;
	t_matrix	*final_transform;

	transform = matrix_rotation_full(fdf->rotation_x, fdf->rotation_y,
		fdf->rotation_z);
	projection = get_projection_matrix(fdf->projection_type);
	if (!transform || !projection)
		return ;
	final_transform = matrix_product(projection, transform);
	if (!final_transform)
		return ;
	apply_matrix_to_points(fdf->coords, final_transform);
	free_matrix(transform);
	free_matrix(projection);
	free_matrix(final_transform);
}
