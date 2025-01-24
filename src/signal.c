/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:18:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/01/24 16:27:24 by ppontet          ###   ########lyon.fr   */
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
	// Pour forcer les appels sur les fonctions enregistrées par atexit
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
	// On enregistre des fonctions à exécuter
	// en cas de sortie normale du processus.
	atexit(exit_function);
	// On enregistre quelques gestionnaires de signaux.
	signal(SIGTERM, &sig_term);
	signal(SIGCONT, &sig_cont);
	// Un message d'accueil.
	printf("Welcome to SignalTest V1.0 :-)\n");
	// La boucle principale de notre console.
	while (true)
	{
		printf("Enter a command: ");
		fflush(stdout);
		scanf("%s", buffer);
		if (strcmp(buffer, "exit") == 0)
			break ;
		if (strcmp(buffer, "help") == 0)
		{
			// Affiche la liste des signaux supportés par le système.
			// Attention : ne marche que sur Linux/Unix !!!
			system("bash -c \"kill -l\"");
			continue ;
		}
		signal_id = atoi(buffer);
		raise(signal_id); // C ISO
							// kill( getpid(), signalId );
							// POSIX (requière <unistd.h>)
	}
	return (EXIT_SUCCESS);
}
