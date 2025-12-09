/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:05:02 by danz              #+#    #+#             */
/*   Updated: 2025/11/26 12:48:45 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

#ifdef __APPLE__
# define ESC_KEY 53
# define UP_KEY 126
# define DOWN_KEY 125
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define PLUS_KEY 24
# define MINUS_KEY 27
# define DESTROY_NOTIFY 17
#else
# define ESC_KEY 65307
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define PLUS_KEY 65451
# define MINUS_KEY 65453
# define DESTROY_NOTIFY 17
#endif

int	cleanup_exit(t_fdf *fdf)
{
	ft_lstclear(&fdf->coords, free_point);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	exit(0);
	return (0);
}

void	reset(t_fdf *fdf)
{
	fdf->rotation_x = 0.0f;
	fdf->rotation_y = 0.0f;
	fdf->rotation_z = 0.0f;
	fdf->scale = 1.0f;
	fdf->offset_x = 0.0f;
	fdf->offset_y = 0.0f;
	fdf->projection_type = ISOMETRIC;
	fdf->needs_render = 1;
}

void	handle_motion(int keycode, t_fdf *fdf)
{
	if (keycode == 'w' || keycode == 'W')
		fdf->rotation_x -= 0.1f;
	if (keycode == 's' || keycode == 'S')
		fdf->rotation_x += 0.1f;
	if (keycode == 'a' || keycode == 'A')
		fdf->rotation_y -= 0.1f;
	if (keycode == 'd' || keycode == 'D')
		fdf->rotation_y += 0.1f;
	if (keycode == 'q' || keycode == 'Q')
		fdf->rotation_z -= 0.1f;
	if (keycode == 'e' || keycode == 'E')
		fdf->rotation_z += 0.1f;
	if (keycode == PLUS_KEY || keycode == '=' || keycode == '+')
		fdf->scale *= 1.1f;
	if (keycode == MINUS_KEY || keycode == '-')
		fdf->scale *= 0.9f;
	if (keycode == UP_KEY)
		fdf->offset_y -= 20.0f;
	if (keycode == DOWN_KEY)
		fdf->offset_y += 20.0f;
	if (keycode == LEFT_KEY)
		fdf->offset_x -= 20.0f;
	if (keycode == RIGHT_KEY)
		fdf->offset_x += 20.0f;
}

int	handle_key(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		cleanup_exit(fdf);
	handle_motion(keycode, fdf);
	if (keycode == 'p' || keycode == 'P')
		fdf->projection_type = !fdf->projection_type;
	if (keycode == 'r' || keycode == 'R')
		reset(fdf);
	fdf->needs_render = 1;
	return (0);
}

short	mlx_create(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (1);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WID, WIN_HGT, "fdf");
	if (!fdf->win)
		return (1);
	fdf->img = mlx_new_image(fdf->mlx, IMG_WID, IMG_HGT);
	if (!fdf->img)
		return (1);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line,
			&fdf->endian);
	fdf->needs_render = 1;
	return (0);
}
