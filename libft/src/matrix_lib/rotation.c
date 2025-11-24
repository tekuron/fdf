/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:16:29 by danz              #+#    #+#             */
/*   Updated: 2025/11/14 12:52:43 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lib.h"

t_matrix	*matrix_rotation_x(float theta)
{
	t_matrix	*ret;

	ret = identity(4);
	if (!ret)
		return (NULL);
	ret->matrix[1][1] = cos((double)theta);
	ret->matrix[1][2] = -sin((double)theta);
	ret->matrix[2][1] = sin((double)theta);
	ret->matrix[2][2] = cos((double)theta);
	return (ret);
}

t_matrix	*matrix_rotation_y(float theta)
{
	t_matrix	*ret;

	ret = identity(4);
	if (!ret)
		return (NULL);
	ret->matrix[0][0] = cos((double)theta);
	ret->matrix[0][2] = sin((double)theta);
	ret->matrix[2][0] = -sin((double)theta);
	ret->matrix[2][2] = cos((double)theta);
	return (ret);
}

t_matrix	*matrix_rotation_z(float theta)
{
	t_matrix	*ret;

	ret = identity(4);
	if (!ret)
		return (NULL);
	ret->matrix[0][0] = cos((double)theta);
	ret->matrix[0][1] = -sin((double)theta);
	ret->matrix[1][0] = sin((double)theta);
	ret->matrix[1][1] = cos((double)theta);
	return (ret);
}

t_matrix	*matrix_rotation_full(float theta_x, float theta_y, float theta_z)
{
	t_matrix	*ret;
	t_matrix	*tmp;
	t_matrix	*rot;

	ret = identity(4);
	rot = matrix_rotation_x(theta_x);
	tmp = matrix_product(ret, rot);
	free_matrix(ret);
	free_matrix(rot);
	ret = tmp;
	rot = matrix_rotation_y(theta_y);
	tmp = matrix_product(ret, rot);
	free_matrix(ret);
	free_matrix(rot);
	ret = tmp;
	rot = matrix_rotation_z(theta_z);
	tmp = matrix_product(ret, rot);
	free_matrix(ret);
	free_matrix(rot);
	ret = tmp;
	if (!ret)
		return (NULL);
	return (ret);
}
