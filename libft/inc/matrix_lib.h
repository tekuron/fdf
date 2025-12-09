/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_lib.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:31:50 by danzamor          #+#    #+#             */
/*   Updated: 2025/11/25 23:44:16 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_LIB_H
# define MATRIX_LIB_H

# include <stdlib.h>
# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_matrix
{
	float	**matrix;
	int		rows;
	int		cols;
}	t_matrix;

t_matrix	*matrix_new(int rows, int cols);
float		**matrix_alloc(int x, int y);
t_matrix	*identity(int size);
void		free_matrix(t_matrix *matrix);
t_matrix	*matrix_product(t_matrix *mat1, t_matrix *mat2);
t_matrix	*matrix_translation(float tx, float ty, float tz);
t_matrix	*matrix_rotation_x(float theta);
t_matrix	*matrix_rotation_y(float theta);
t_matrix	*matrix_rotation_z(float theta);
t_matrix	*matrix_rotation_full(float theta_x, float theta_y, float theta_z);
t_matrix	*matrix_isometric_projection(void);
t_matrix	*matrix_cavalier_projection(void);

#endif