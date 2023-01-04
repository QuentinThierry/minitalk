/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:33:56 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/04 18:11:11 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_BONUS_H
# define SERVEUR_BONUS_H

// # define _XOPEN_SOURCE 700 // fix erreur vscode

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>

size_t	ft_strlen(const char *s);
void	ft_bzero(int *s, size_t n);
void	ft_putnbr_fd(int n, int fd);

#endif