/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:09:30 by danz              #+#    #+#             */
/*   Updated: 2025/11/25 20:18:49 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_pars.h"
#include "mlx_manage.h"
#include "libft.h"
#include "ft_printf_bonus.h"
#include "mlx.h"
#include <stdio.h>

static void	apply_osd(t_fdf *fdf_prev, t_fdf *fdf)
{
	t_list	*coords;
	t_point	*cur;
	float	center_x;
	float	center_y;
	float	prev_scale;

	coords = fdf->coords;
	prev_scale = fdf_prev->scale;
	center_x = IMG_WID / 2.0f;
	center_y = IMG_HGT / 2.0f;
	while (coords)
	{
		cur = coords->content;
		cur->osd[0] -= center_x / prev_scale - center_x / fdf->scale;
		cur->osd[1] -= center_y / prev_scale - center_y / fdf->scale;
		cur->osd[0] += fdf->offset_x - fdf_prev->offset_x;
		cur->osd[1] += fdf->offset_y - fdf_prev->offset_y;
		cur->osd[0] *= fdf->scale / prev_scale;
		cur->osd[1] *= fdf->scale / prev_scale;
		coords = coords->next;
	}
}

void	save_prev(t_fdf *fdf_prev, t_fdf *fdf)
{
	fdf_prev->offset_x = fdf->offset_x;
	fdf_prev->offset_y = fdf->offset_y;
	fdf_prev->projection_type = fdf->projection_type;
	fdf_prev->rotation_x = fdf->rotation_x;
	fdf_prev->rotation_y = fdf->rotation_y;
	fdf_prev->rotation_z = fdf->rotation_z;
	fdf_prev->scale = fdf->scale;
}

int	render_frame(t_fdf *fdf)
{
	static t_fdf	fdf_prev;
	static int		start;

	if (fdf->needs_render)
	{
		ft_bzero(fdf->addr, IMG_WID * IMG_HGT * (fdf->bpp / 8));
		if (!start)
			save_prev(&fdf_prev, fdf);
		if (fdf->rotation_x != fdf_prev.rotation_x ||
			fdf->rotation_y != fdf_prev.rotation_y ||
			fdf->rotation_z != fdf_prev.rotation_z ||
			fdf->projection_type != fdf_prev.projection_type ||
			!start)
		{
			apply_transformations(fdf);
			save_osd(fdf);
			start = 1;
		}
		apply_osd(&fdf_prev, fdf);
		draw_lines(*fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
		fdf->needs_render = 0;
		save_prev(&fdf_prev, fdf);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (ft_printf("Usage: ./fdf <filename>\n"));
	fdf.coords = pars(argv[1]);
	if (!fdf.coords)
		return (ft_printf("Error: Failed to parse map file\n"));
	fdf.rotation_x = 0.0f;
	fdf.rotation_y = 0.0f;
	fdf.rotation_z = 0.0f;
	fdf.scale = 1.0f;
	fdf.offset_x = 0.0f;
	fdf.offset_y = 0.0f;
	fdf.projection_type = ISOMETRIC;
	if (mlx_create(&fdf))
		cleanup_exit(&fdf);
	mlx_hook(fdf.win, 2, 1L << 0, handle_key, &fdf);
	mlx_hook(fdf.win, 17, 1L << 17, cleanup_exit, &fdf);
	mlx_loop_hook(fdf.mlx, render_frame, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
