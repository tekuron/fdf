/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:02:15 by danz              #+#    #+#             */
/*   Updated: 2025/11/14 14:49:52 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_point(void *point)
{
	free_matrix(((t_point *)point)->coords);
	if (((t_point *)point)->iso_coords)
		free_matrix(((t_point *)point)->iso_coords);
	free(point);
}
