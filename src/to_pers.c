/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_pers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:17:10 by danz              #+#    #+#             */
/*   Updated: 2025/11/22 00:51:09 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

short	save_iso(t_list *coords)
{
	t_matrix	*iso;
	t_point		*point;

	iso = matrix_isometric_projection();
	while (coords)
	{
		point = (t_point *)coords->content;
		point->iso_coords = matrix_product(iso, point->coords);
		if (!point->iso_coords)
			return (1);
		coords = coords->next;
	}
	free_matrix(iso);
	return (0);
}

short	save_conic(t_list *coords)
{
	t_matrix	*iso;
	t_point		*point;

	iso = matrix_perspective_projection();
	while (coords)
	{
		point = (t_point *)coords->content;
		point->iso_coords = matrix_product(iso, point->coords);
		if (!point->iso_coords)
			return (1);
		coords = coords->next;
	}
	free_matrix(iso);
	return (0);
}
