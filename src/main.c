/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:09:30 by danz              #+#    #+#             */
/*   Updated: 2025/11/22 19:37:33 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_pars.h"
#include "mlx_manage.h"
#include "libft.h"
#include "ft_printf_bonus.h"
#include "mlx.h"
#include <stdio.h>

int	render_frame(t_fdf *fdf)
{
	if (fdf->needs_render)
	{
		ft_bzero(fdf->addr, IMG_WID * IMG_HGT * (fdf->bpp / 8));
		apply_transformations(fdf);
		if (fdf->projection_type == ISOMETRIC)
			save_iso(fdf->coords);
		else
			save_conic(fdf->coords);
		save_osd(fdf->coords);
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = mlx_new_image(fdf->mlx, IMG_WID, IMG_HGT);
		fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line,
			&fdf->endian);
		draw_lines(*fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
		fdf->needs_render = 0;
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
	if (save_iso(fdf.coords))
		return (ft_printf("Error: Failed to apply isometric projection\n"));
	save_osd(fdf.coords);
	if (mlx_create(&fdf))
		cleanup_exit(&fdf);
	mlx_hook(fdf.win, 2, 1L << 0, handle_key, &fdf);
	mlx_hook(fdf.win, 17, 1L << 17, cleanup_exit, &fdf);
	mlx_loop_hook(fdf.mlx, render_frame, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
