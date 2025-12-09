/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:40:17 by danz              #+#    #+#             */
/*   Updated: 2025/11/26 12:53:56 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lib.h"

t_matrix	*matrix_isometric_projection(void)
{
	t_matrix	*ret;

	ret = matrix_new(4, 4);
	if (!ret)
		return (NULL);
	ret->matrix[0][0] = cos(M_PI / 6);
	ret->matrix[0][1] = -cos(M_PI / 6);
	ret->matrix[1][0] = sin(M_PI / 6);
	ret->matrix[1][1] = sin(M_PI / 6);
	ret->matrix[1][2] = -1;
	ret->matrix[3][3] = 1;
	return (ret);
}

t_matrix	*matrix_cavalier_projection(void)
{
	t_matrix	*ret;
	float		f;
	float		aspect;

	ret = matrix_new(4, 4);
	if (!ret)
		return (NULL);
	f = 1.0f / tan(M_PI / 6);
	aspect = 1.9f;
	ret->matrix[0][0] = f / aspect;
	ret->matrix[1][1] = f;
	ret->matrix[2][2] = 1000.1f / (-999.9f);
	ret->matrix[2][3] = (1000.0f * 2 * 0.1f) / (-999.9f);
	ret->matrix[3][2] = -1;
	return (ret);
}
