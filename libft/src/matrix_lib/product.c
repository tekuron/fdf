/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   product.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:32:24 by danzamor          #+#    #+#             */
/*   Updated: 2025/10/23 12:55:55 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lib.h"

static t_matrix	*multiplication(t_matrix *mat1, t_matrix *mat2)
{
	t_matrix	*ret;
	int			i;
	int			j;
	int			k;

	ret = matrix_new(mat1->rows, mat2->cols);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < mat1->rows)
	{
		j = -1;
		while (++j < mat2->cols)
		{
			k = -1;
			while (++k < mat1->cols)
				ret->matrix[i][j] += mat1->matrix[i][k] * mat2->matrix[k][j];
		}
	}
	return (ret);
}

t_matrix	*matrix_product(t_matrix *mat1, t_matrix *mat2)
{
	t_matrix	*ret;

	if (!mat1 || !mat2)
		return (NULL);
	if (mat1->cols != mat2->rows)
		return (NULL);
	ret = multiplication(mat1, mat2);
	if (!ret)
		return (NULL);
	return (ret);
}
