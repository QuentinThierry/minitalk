/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:31:15 by qthierry          #+#    #+#             */
/*   Updated: 2022/12/06 05:35:26 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	g_has_return_sig;

void	send_signal_zero(int pid)
{
	kill(pid, SIGUSR1);
}

void	send_signal_one(int pid)
{
	kill(pid, SIGUSR2);
}

void afficher_binaire(int n) {
	for(int i = 31*sizeof(char); i >= 0; --i) {
		putchar((n & (1 << i)) ? '1' : '0');
	}
}

void	set_ready(int to_add)
{
	(void)to_add;
	g_has_return_sig = 1;
}


int main(int argc, char const *argv[])
{
	int		pid;
	size_t	size;
	size_t	i;
	size_t	j;
	size_t	value;
	struct	sigaction act;

	g_has_return_sig = 1;
	sigemptyset(&act.sa_mask);
	// act.sa_flags = SA_SIGINFO;
	act.sa_handler = &set_ready;
	sigaction(SIGUSR1, &act, NULL);
	if (argc < 3)
		return (EXIT_FAILURE);
	pid = atoi(argv[1]);
	size = strlen(argv[2]);

	i = 0;
	while (i <= size)
	{
		j = 0;
		value = argv[2][i];
		while (j < 8)
		{
			g_has_return_sig = 0;
			if (!(value & 0x80))
				send_signal_zero(pid);
			else
				send_signal_one(pid);
			value <<= 1;
			j++;
			while (!g_has_return_sig)
			{
			}
		}
		i++;
	}
	return 0;
}
