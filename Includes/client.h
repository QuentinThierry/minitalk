/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:34:34 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/04 16:57:11 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define _XOPEN_SOURCE 700 // fix erreur vscode

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);

#endif