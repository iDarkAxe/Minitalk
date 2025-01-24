/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:24:30 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/24 21:24:50 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	sig_cont(int code)
{
	printf(">>> SIGCONT received [%d]\n", code);
}

void	sig_term(int code)
{
	fprintf(stderr, ">>> SIGTERM received [%d]\n", code);
	exit(EXIT_SUCCESS);
}

void	exit_function(void)
{
	printf("Exiting...\n");
}

int	main(void)
{
	int		signal_id;
	char	buffer[100];

	atexit(exit_function);
	signal(SIGTERM, &sig_term);
	signal(SIGCONT, &sig_cont);
	printf("Welcome to SignalTest V1.0 :-)\n");
	while (true)
	{
		printf("Enter a command: ");
		fflush(stdout);
		scanf("%s", buffer);
		if (strcmp(buffer, "exit") == 0)
			break ;
		if (strcmp(buffer, "help") == 0)
		{
			system("bash -c \"kill -l\"");
			continue ;
		}
		signal_id = atoi(buffer);
		raise(signal_id);
	}
	return (EXIT_SUCCESS);
}
