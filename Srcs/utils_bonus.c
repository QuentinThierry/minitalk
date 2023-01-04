/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 04:33:51 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/04 16:59:34 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/serveur.h"

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

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	ncpy;
	char			c;

	ncpy = n * (1 | -(n < 0));
	if (n < 0)
		write(fd, "-", 1);
	if (ncpy >= 10)
	{
		ft_putnbr_fd(ncpy / 10, fd);
		ft_putnbr_fd(ncpy % 10, fd);
	}
	else
	{
		c = ncpy + '0';
		write(fd, &c, 1);
	}
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (!(*nptr >= '0' && *nptr <= '9'))
	{
		if (*nptr == '-')
			sign = -1;
		else if (*nptr != '+')
			return (-1);
		nptr++;
	}
	while ((*nptr >= '0' && *nptr <= '9'))
		res = res * 10 + *nptr++ - '0';
	return (res * sign);
}
