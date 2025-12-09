/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:20:08 by danz              #+#    #+#             */
/*   Updated: 2025/10/23 12:55:55 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lib.h"

void	free_matrix(t_matrix *matrix)
{
	int		i;

	i = 0;
	while (i < matrix->rows)
	{
		free(matrix->matrix[i]);
		i++;
	}
	free(matrix->matrix);
	free(matrix);
}

float	**matrix_alloc(int x, int y)
{
	float	**ret;
	int		i;

	i = 0;
	ret = malloc(x * (sizeof(float *)));
	if (!ret)
		return (NULL);
	while (i < x)
	{
		ret[i] = malloc(y * sizeof(float));
		if (!ret[i])
		{
			while (i--)
				free(ret[i]);
			return (free(ret), NULL);
		}
		i++;
	}
	return (ret);
}

t_matrix	*matrix_new(int rows, int cols)
{
	t_matrix	*ret;
	int			i;
	int			j;

	ret = malloc(sizeof(t_matrix));
	if (!ret)
		return (NULL);
	ret->matrix = matrix_alloc(rows, cols);
	if (!ret->matrix)
		return (free_matrix(ret), NULL);
	ret->rows = rows;
	ret->cols = cols;
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
			ret->matrix[i][j] = 0;
	}
	return (ret);
}
