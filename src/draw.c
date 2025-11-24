/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:00:00 by Copilot           #+#    #+#             */
/*   Updated: 2025/11/21 15:39:52 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>

static void	init_bresenham(t_point p0, t_point p1, int *params)
{
	params[0] = abs(p1.osd[0] - p0.osd[0]);
	params[1] = abs(p1.osd[1] - p0.osd[1]);
	if (p0.osd[0] < p1.osd[0])
		params[2] = 1;
	else
		params[2] = -1;
	if (p0.osd[1] < p1.osd[1])
		params[3] = 1;
	else
		params[3] = -1;
	params[4] = params[0] - params[1];
}

void	draw_line(t_point p0, t_point p1, t_fdf fdf)
{
	int	params[5];
	int	pos[2];
	int	e2;

	init_bresenham(p0, p1, params);
	pos[0] = p0.osd[0];
	pos[1] = p0.osd[1];
	while (1)
	{
		put_pixel(pos[0], pos[1], lerp(p0, p1, pos), fdf);
		if (pos[0] == p1.osd[0] && pos[1] == p1.osd[1])
			break ;
		e2 = 2 * params[4];
		if (e2 > -params[1])
		{
			params[4] -= params[1];
			pos[0] += params[2];
		}
		if (e2 < params[0])
		{
			params[4] += params[0];
			pos[1] += params[3];
		}
	}
}

static t_point	*find_point(t_list *coords, int x, int y)
{
	t_list	*cur;
	t_point	*point;

	cur = coords;
	while (cur)
	{
		point = cur->content;
		if ((int)point->coords->matrix[0][0] == x
			&& (int)point->coords->matrix[1][0] == y)
			return (point);
		cur = cur->next;
	}
	return (NULL);
}

void	draw_lines(t_fdf fdf)
{
	t_list	*cur;
	t_point	*point;
	t_point	*adjacent;
	int		x;
	int		y;

	if (!fdf.coords)
		return ;
	cur = fdf.coords;
	while (cur)
	{
		point = cur->content;
		x = (int)point->coords->matrix[0][0];
		y = (int)point->coords->matrix[1][0];
		adjacent = find_point(fdf.coords, x + 1, y);
		if (adjacent)
			draw_line(*point, *adjacent, fdf);
		adjacent = find_point(fdf.coords, x, y + 1);
		if (adjacent)
			draw_line(*point, *adjacent, fdf);
		cur = cur->next;
	}
}
