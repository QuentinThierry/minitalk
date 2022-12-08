/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:21:13 by qthierry          #+#    #+#             */
/*   Updated: 2022/12/08 01:22:36 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int	*g_tab;

void afficher_binaire(int n) {
	for(int i = 31*sizeof(char); i >= 0; --i) {
		putchar((n & (1 << i)) ? '1' : '0');
	}
	putchar('\n');
}

static int	*allocate_tab()
{
	unsigned int	tmp;
	int				*res;

	tmp = g_tab[1] - 0x80000000;
	//printf("tmp alloc : %d\n", tmp + 3);
	free(g_tab);
	res = malloc(sizeof(char) * (tmp + 4));
	if (!res)
		return (NULL);
	ft_bzero(res, (int)(tmp + 4));
	res[0] = 1;
	res[1] = 0;
	res[2] = 0;
	res[3] = (int)tmp;
	return (res);
}

void	add_to_buffer(int to_add, siginfo_t *info, void* vp)
{
	(void)vp;

	// fill length
	if (g_tab[0] == 0)
	{
		g_tab[1] <<= 1;
		g_tab[1] += (to_add == SIGUSR2);
		if (g_tab[1] & 0x80000000)
		{
			g_tab = allocate_tab();
			if (!g_tab)
				exit(EXIT_FAILURE);
		}
	}
	else
	{
		//printf("meta : %d, %d, %d, %d\n", g_tab[0], g_tab[1], g_tab[2], g_tab[3]);

		g_tab[g_tab[1] + 4] <<= 1;
		g_tab[g_tab[1] + 4] += (to_add == SIGUSR2);
		g_tab[2]++;
		//afficher_binaire(g_tab[g_tab[1] + 4]);
		//write(1, "\n", 1);
		//printf("g_tab[%d] = %d\n", g_tab[1] + 4, g_tab[g_tab[1] + 4]);
		if (g_tab[2] == 32)
		{
			//printf("final : %d\n", g_tab[g_tab[1] + 4]);
			g_tab[2] = 0;
			//afficher_binaire(g_tab[g_tab[1] + 4]);
			g_tab[1]++;
		}
		if (g_tab[1] == (g_tab[3] / 4))
		{
			for (int i = 0; i < g_tab[1]; i++)
			{
				for (int j = 3; j >= 0; j--)
				{
					printf("%c", (*(g_tab + 4 + i)) >> j * 8);
					fflush(stdout);
				}
			}
			
			//printf("%s\n", (char *)(g_tab + 4));
			ft_bzero(g_tab, g_tab[1] + 4);
			g_tab[0] = 0;
			g_tab[1] = 0x1;
		}
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

	(void)argc;
	(void)argv;
	print_pid();
	g_tab = malloc(sizeof(char) * 2);
	if (!g_tab)
		return (EXIT_FAILURE);
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	g_tab[0] = 0;
	g_tab[1] = 0x1;
	act.sa_sigaction = &add_to_buffer;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
