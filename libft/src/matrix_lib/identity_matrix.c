/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:26:54 by danz              #+#    #+#             */
/*   Updated: 2025/10/23 12:55:55 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_lib.h"

t_matrix	*identity(int size)
{
	t_matrix	*ret;
	int			i;

	ret = matrix_new(size, size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret->matrix[i][i] = 1;
		i++;
	}
	return (ret);
}
