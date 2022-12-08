/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:31:15 by qthierry          #+#    #+#             */
/*   Updated: 2022/12/08 00:58:45 by qthierry         ###   ########.fr       */
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
	size = strlen(argv[2]) + 1;
	value = size;
	i = 0;
	j = 0;

	while (j < 31)
	{
		if (j == 0)
			value <<= 1;
		g_has_return_sig = 0;
		//printf("send : %ld\n", (value & 0x40000000));
		if (!(value & 0x80000000))
			send_signal_zero(pid);
		else
			send_signal_one(pid);
		value <<= 1;
		j++;
		while (!g_has_return_sig)
		{
		}
	}

	while (i < size)
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
			//printf("send : %ld, argv : %c\n", (value & 0x80), argv[2][i]);
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
