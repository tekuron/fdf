/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manage.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:16:32 by danz              #+#    #+#             */
/*   Updated: 2025/11/22 01:02:13 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_MANAGE_H
# define MLX_MANAGE_H

short	mlx_create(t_fdf *fdf);
int		handle_key(int keycode, t_fdf *fdf);

#endif