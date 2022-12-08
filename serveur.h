/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:33:56 by qthierry          #+#    #+#             */
/*   Updated: 2022/12/08 01:04:46 by qthierry         ###   ########.fr       */
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
#include <strings.h>

size_t	ft_strlen(const char *s);
void	ft_bzero(int *s, size_t n);

#endif