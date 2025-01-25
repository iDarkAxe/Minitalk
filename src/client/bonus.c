/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:21:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/25 13:10:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

static int ft_atoi(const char *nptr);

int	find_server_pid(int argc, char **argv, char **string, pid_t *g_server_pid)
{
	int		fd;
	char	pid_buffer[10];

	if (argc == 3)
	{
		*g_server_pid = ft_atoi(argv[1]);
		*string = argv[2];
		return (*g_server_pid);
	}
	*string = argv[1];
	system("ps aux | grep \
		-v \"grep\" | grep \" ./server\" | awk '{print $2}' > .pid");
	fd = open(".pid", O_RDONLY | O_CREAT);
	if (fd == -1)
	{
		ft_printf("Error\nNo server found\n");
		exit(1);
	}
	pid_buffer[read(fd, pid_buffer, 10)] = '\0';
	close(fd);
	remove(".pid");
	fd = ft_atoi(pid_buffer);
	return (fd);
}

/**
 * @brief Convert string to int, and handle number
 *
 * @param nptr String to convert
 * @return int Converted number
 */
static int	ft_atoi(const char *nptr)
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
