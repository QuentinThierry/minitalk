/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qthierry <qthierry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:31:15 by qthierry          #+#    #+#             */
/*   Updated: 2023/01/04 16:59:03 by qthierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/client.h"

int	g_has_return_sig;

void	set_ready(int to_add, siginfo_t *info, void *vp)
{
	(void)to_add;
	(void)info;
	(void)vp;
	g_has_return_sig = 1;
}

void	send_length(int size, pid_t pid)
{
	size_t	j;
	size_t	size_int;

	j = 0;
	size_int = sizeof(int) * 8;
	while (j < size_int - 1)
	{
		g_has_return_sig = 0;
		if (j == 0)
			size <<= 1;
		if (!(size & 0x80000000))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		size <<= 1;
		j++;
		while (!g_has_return_sig)
			;
	}
}

void	send_string(size_t size, char const **argv, pid_t pid)
{
	size_t	i;
	size_t	j;
	size_t	value;
	size_t	size_char;

	i = 0;
	value = size;
	size_char = 8 * sizeof(char);
	while (i < size)
	{
		j = 0;
		value = argv[2][i];
		while (j++ < size_char)
		{
			g_has_return_sig = 0;
			if (!(value & 0x80))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			value <<= 1;
			while (!g_has_return_sig)
				;
		}
		i++;
	}
}

int	main(int argc, char const **argv)
{
	int					pid;
	size_t				size;
	struct sigaction	act;

	g_has_return_sig = 0;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &set_ready;
	sigaction(SIGUSR1, &act, NULL);
	if (argc != 3)
		return (EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	if (pid < 0)
		return (1);
	size = ft_strlen(argv[2]) + 1;
	send_length(size, pid);
	send_string(size, argv, pid);
	return (EXIT_SUCCESS);
}
