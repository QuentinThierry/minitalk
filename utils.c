/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 04:33:51 by qthierry          #+#    #+#             */
/*   Updated: 2022/12/08 01:04:41 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i-- > 0)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	const char	*cpy;

	cpy = s;
	while (*s)
		s++;
	return ((size_t)(s - cpy));
}

void	ft_bzero(int *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		s[i++] = 0;
}

//int	lst_add_back(t_list **list, char *content)
//{
//	t_list	*tmp;
//	t_list	*added;

//	if (!content || !*content)
//		return (1);
//	added = malloc(sizeof(t_list));
//	if (!added)
//		return (0);
//	ft_memmove(added->buffer, content, ft_strlen(content) + 1);
//	added->next = NULL;
//	if (!*list)
//	{
//		*list = added;
//		return (1);
//	}
//	tmp = *list;
//	while (tmp->next)
//		tmp = tmp->next;
//	tmp->next = added;
//	return (1);
//}