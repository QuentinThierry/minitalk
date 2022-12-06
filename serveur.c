/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:21:13 by qthierry          #+#    #+#             */
/*   Updated: 2022/12/06 05:36:06 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int	g_buffer;

int	fill_tab(char (*tab)[])
{
	size_t	i;

	i = 0;
	if (!(g_buffer & 0xff))
	{
		// printf("%s", *tab);
		write(1, *tab, ft_strlen(*tab));
		fflush(stdout);
		return (0);
	}
	while (i < 1024)
	{
		if ((*tab)[i] == 0)
		{
			(*tab)[i] = (char)(g_buffer & 0xff);
			return (1);
		}
		i++;
	}
	write(1, *tab, 1024);
	ft_bzero(*tab, 1024);
	fflush(stdout);
	return (1);
}

void	add_to_buffer(int to_add, siginfo_t *info, void* vp)
{
	static	char tab[1024] = {0};

	(void)vp;
	g_buffer <<= 1;
	g_buffer += (to_add == SIGUSR2);
	if ((g_buffer & 0xff00) == 0xff00)
	{
		if (fill_tab(&tab) == 0)
		{
			kill(info->si_pid, SIGUSR1);
			g_buffer = 0xff;
			ft_bzero(tab, 1024);
			return ;
		}
		g_buffer = 0xff;
	}
	kill(info->si_pid, SIGUSR1);
}


void	print_pid()
{
	printf("%d\n", getpid());
}

int main(int argc, char const *argv[])
{
	struct sigaction	act;
	char				*res;

	print_pid();
	g_buffer = 0x1;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	g_buffer = 0xff;
	act.sa_sigaction = &add_to_buffer;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
		
	}
	free(res);
	return (0);
}
