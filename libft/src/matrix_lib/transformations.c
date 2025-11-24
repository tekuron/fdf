/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:31:07 by danz              #+#    #+#             */
/*   Updated: 2025/11/14 12:19:12 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lib.h"

t_matrix	*matrix_translation(float tx, float ty, float tz)
{
	t_matrix	*ret;

	ret = identity(4);
	if (!ret)
		return (NULL);
	ret->matrix[0][3] = tx;
	ret->matrix[1][3] = ty;
	ret->matrix[2][3] = tz;
	return (ret);
}

t_matrix	*matrix_scale(float sx, float sy, float sz)
{
	t_matrix	*ret;

	ret = identity(4);
	if (!ret)
		return (NULL);
	ret->matrix[0][0] = sx;
	ret->matrix[1][1] = sy;
	ret->matrix[2][2] = sz;
	return (ret);
}
