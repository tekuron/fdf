/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:23:41 by danz              #+#    #+#             */
/*   Updated: 2025/11/25 20:36:45 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_pars.h"
#include "get_next_line.h"
#include "mlx.h"

static short	save_point(char **buf, t_point *point, int *p_l)
{
	t_matrix	*new;

	new = matrix_new(4, 1);
	if (!new)
		return (-1);
	point->coords = new;
	new->matrix[0][0] = (float)p_l[0];
	new->matrix[1][0] = (float)p_l[1];
	new->matrix[2][0] = (float)ft_atoi(*buf) / 2;
	new->matrix[3][0] = 1;
	while (**buf >= '0' && **buf <= '9')
		(*buf)++;
	if (**buf == ',')
	{
		(*buf)++;
		point->color = htoi(*buf);
		while (**buf && **buf != ' ')
			(*buf)++;
	}
	else
		point->color = color_calc(0x2E1065, 0xB19CD9, point->coords->matrix[2][0] / 20);
	point->iso_coords = 0;
	return (0);
}

static short	add_point_to_list(t_list **ret, t_list **tail, t_point *point)
{
	t_list	*new_node;

	new_node = ft_lstnew(point);
	if (!new_node)
	{
		free(point);
		return (-1);
	}
	if (*tail)
		(*tail)->next = new_node;
	else
		*ret = new_node;
	*tail = new_node;
	return (0);
}

static short	pars_mod(t_list **ret, t_list **tail, char **tmp, int *p_l)
{
	t_point	*point;

	if (**tmp >= '0' && **tmp <= '9')
	{
		point = (t_point *)malloc(sizeof(t_point));
		if (!point)
			return (-1);
		if (add_point_to_list(ret, tail, point) == -1)
			return (-1);
		if (save_point(tmp, point, p_l) == -1)
			return (-1);
		p_l[0]++;
	}
	else
		(*tmp)++;
	return (0);
}

static short	process_line(char *buf, t_list **ret, t_list **tail, int *p_l)
{
	char	*tmp;

	tmp = buf;
	p_l[0] = 1;
	while (*tmp)
	{
		if (pars_mod(ret, tail, &tmp, p_l) == -1)
			return (-1);
	}
	return (0);
}

t_list	*pars(char *filename)
{
	char	*buf;
	t_list	*ret;
	t_list	*tail;
	int		fd;
	int		p_l[2];

	fd = open(filename, O_RDONLY);
	buf = get_next_line(fd);
	p_l[1] = 1;
	ret = 0;
	tail = 0;
	while (buf)
	{
		if (process_line(buf, &ret, &tail, p_l) == -1)
			return (err_exit(&ret, buf, fd));
		free(buf);
		buf = get_next_line(fd);
		p_l[1]++;
	}
	close(fd);
	return (ret);
}
