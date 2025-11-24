/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:58:22 by danz              #+#    #+#             */
/*   Updated: 2025/11/21 19:06:20 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "fdf_pars.h"

static int	onehextoint(char c)
{
	if (c <= '9' && c >= '0')
		return (c - 48);
	else if (c <= 'z' && c >= 'a')
		return (c - 97 + 10);
	else if (c <= 'Z' && c >= 'A')
		return (c - 65 + 10);
	return (-1);
}

int	htoi(char *hex)
{
	char	base[17];
	int		ret;

	(void)ft_strlcpy(base, "0123456789abcdef", 17);
	ret = 0;
	if (hex[0] == '0' && hex[1] == 'x')
		hex += 2;
	while (*hex && onehextoint(*hex) != -1)
	{
		ret *= 16;
		ret += onehextoint(*hex);
		hex++;
	}
	return (ret);
}

void	*err_exit(t_list **ret, char *buf, int fd)
{
	ft_lstclear(ret, free_point);
	free(buf);
	close(fd);
	return (NULL);
}
