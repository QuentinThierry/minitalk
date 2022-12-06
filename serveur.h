/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:33:56 by qthierry          #+#    #+#             */
/*   Updated: 2022/12/06 05:32:14 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

#define _XOPEN_SOURCE 700 // a enlever, fix erreur vscode

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	char			buffer[1024];
	struct s_list	*next;
}	t_list;

int	lst_add_back(t_list **list, char *content);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);

#endif