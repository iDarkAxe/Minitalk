/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:09:46 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/24 19:10:23 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <signal.h>
// A SUPPRIMER
#include <fcntl.h>
#include <stdlib.h>

int	find_pid(void);
int	ft_atoi(const char *nptr);

int	find_pid(void)
{
	int		fd;
	char	pid_buffer[10];

	system("ps aux | grep \
		-v \"grep\" | grep \" ./server\" | awk '{print $2}' > .pid");
	fd = open(".pid", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nNo server found\n");
		exit(1);
	}
	pid_buffer[read(fd, pid_buffer, 10)] = '\0';
	close(fd);
	fd = ft_atoi(pid_buffer);
	ft_printf("Server PID: %d\n", fd);
	return (fd);
}

int	main(int argc, char **argv)
{
	__pid_t	server_pid;
	size_t	index;
	char	bit;
	char	*string;

	if (argc < 2 || argc > 3)
	{
		ft_printf("Error\nNo argument\n");
		ft_printf("Usage: %s <PID> <SIGNAL>\n", argv[0]);
		exit (-1);
	}
	if (argc == 2)
	{
		server_pid = find_pid();
		string = argv[1];
	}
	else
	{
		server_pid = ft_atoi(argv[1]);
		string = argv[2];
	}
	if (server_pid == 0)
	{
		ft_printf("Error\nInvalid PID\n");
		exit (-1);
	}
	index = 0;
	while (index < 6)
	{
		bit = 0;
		// ft_printf("%c is %d %d %d %d . %d %d %d %d\n", string[index], string[index] & 0x80, string[index] & 0x40, string[index] & 0x20, string[index] & 0x10, string[index] & 0x08, string[index] & 0x04, string[index] & 0x02, string[index] & 0x01);
		while (bit < 8)
		{
			// ft_printf("Trying %d bit:%d\n", string[index] & (0x1 << bit), bit);
			if (string[index] & (128 >> bit))
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(500);
			bit++;
		}
		index++;
	}
	return (0);
}

/**
 * @brief Convert string to int, and handle number
 *
 * @param nptr Pointer to the string
 * @return int value converted
 */
int	ft_atoi(const char *nptr)
{
	long		number;
	long		overflow_tester;
	short int	minus_sign;

	number = 0;
	minus_sign = 0;
	while (*nptr != '\0' && (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
			|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f'))
		nptr++;
	if (*nptr != '\0' && ((*nptr == '-') || (*nptr == '+')))
	{
		if (*nptr == '-')
			minus_sign = -1;
		nptr++;
	}
	while (*nptr != '\0' && *nptr >= '0' && *nptr <= '9')
	{
		overflow_tester = number;
		number = number * 10 + *nptr++ - '0';
		if (overflow_tester > number)
			return (-(!minus_sign));
	}
	if (minus_sign == -1)
		return ((int)-number);
	return ((int)number);
}
