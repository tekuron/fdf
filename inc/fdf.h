/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:29 by danz              #+#    #+#             */
/*   Updated: 2025/11/25 19:20:39 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "matrix_lib.h"
# include "libft.h"

# define WIN_WID 1920
# define WIN_HGT 1080
# define IMG_WID (WIN_WID - WIN_WID / 5)
# define IMG_HGT 1080

# define ISOMETRIC 0
# define PERSPECTIVE 1

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	t_list	*coords;
	int		bpp;
	int		size_line;
	int		endian;
	int		needs_render;
	int		h_range[2];
	float	rotation_x;
	float	rotation_y;
	float	rotation_z;
	float	scale;
	float	offset_x;
	float	offset_y;
	int		projection_type;
}	t_fdf;

typedef struct s_point
{
	t_matrix	*coords;
	t_matrix	*iso_coords;
	int			osd[2];
	int			color;
}	t_point;

t_list	*pars(char *filename);
void	free_point(void *point);
short	save_iso(t_list *coords);
short	save_conic(t_list *coords);
void	save_osd(t_fdf *fdf);
void	put_pixels(t_fdf fdf);
void	put_pixel(int x, int y, int color, t_fdf fdf);
int		lerp(t_point p0, t_point p1, int pos[2]);
void	draw_lines(t_fdf fdf);
int		color_calc(int color0, int color1, float ratio);
void	apply_transformations(t_fdf *fdf);
int		cleanup_exit(t_fdf *fdf);

#endif