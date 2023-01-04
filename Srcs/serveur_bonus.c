/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:21:13 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/04 18:02:14 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/serveur_bonus.h"

int	*g_tab;

static int	*allocate_tab(void)
{
	unsigned int	tmp;
	int				*res;

	tmp = g_tab[1] - 0x80000000;
	free(g_tab);
	res = malloc(sizeof(int) * (tmp + 4));
	if (!res)
		return (NULL);
	ft_bzero(res, (int)(tmp + 4));
	res[0] = 1;
	res[1] = 0;
	res[2] = 0;
	res[3] = (int)tmp;
	return (res);
}

void	handle_characters(int to_add)
{
	char	*tmp;
	long	size;
	long	i;

	g_tab[g_tab[1] + 4] <<= 1;
	g_tab[g_tab[1] + 4] += (to_add == SIGUSR2);
	g_tab[2]++;
	if (g_tab[2] == 8)
	{
		g_tab[2] = 0;
		g_tab[1]++;
	}
	if (g_tab[1] != g_tab[3])
		return ;
	size = sizeof(char) * g_tab[1];
	i = -1;
	tmp = malloc(size);
	if (!tmp)
		exit ((free(g_tab), EXIT_FAILURE));
	while (++i < size)
		tmp[i] = g_tab[i + 4] & 0xff;
	write(1, tmp, size);
	free(tmp);
	free(g_tab);
	g_tab = NULL;
}

void	on_signal(int to_add, siginfo_t *info, void *vp)
{
	(void)vp;
	if (!g_tab)
	{
		g_tab = malloc(sizeof(int) * 2);
		if (!g_tab)
			exit(EXIT_FAILURE);
		g_tab[0] = 0;
		g_tab[1] = 0x1;
	}
	if (g_tab[0] == 0)
	{
		g_tab[1] <<= 1;
		g_tab[1] += (to_add == SIGUSR2);
		if (g_tab[1] & 0x80000000)
		{
			g_tab = allocate_tab();
			if (!g_tab)
				exit((EXIT_FAILURE));
		}
	}
	else
		handle_characters(to_add);
	kill(info->si_pid, SIGUSR1);
}

void	print_pid(void)
{
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
}

int	main(void)
{
	struct sigaction	act;

	print_pid();
	g_tab = NULL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &on_signal;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		;
	return (0);
}
