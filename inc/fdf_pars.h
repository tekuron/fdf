/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_pars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danz <danz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:08:25 by danz              #+#    #+#             */
/*   Updated: 2025/11/21 15:35:38 by danz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_PARS_H
# define FDF_PARS_H

int		htoi(char *hex);
t_list	*pars(char *filename);
void	*err_exit(t_list **ret, char *buf, int fd);

#endif