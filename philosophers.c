/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:33:26 by hduflos           #+#    #+#             */
/*   Updated: 2024/12/20 07:55:56 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Fonction pour init les threads des philosophes qui nettoie en cas d'erreur
int	create_philo_threads(pthread_t *th, t_philo **philo, int nb_philo)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&th[i], NULL, eating, (void *)&((*philo)[i])) != 0)
		{
			j = 0;
			while (j < i)
			{
				if (pthread_join(th[j], NULL) != 0)
					error_handle("Error during pthread_join\n");
				j++;
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

// Fonction pour attendre la fin de tous les threads
void	join_all_threads(pthread_t checker, pthread_t *threads, int nb_philo)
{
	int	i;

	if (pthread_join(checker, NULL) != 0)
		error_handle("Error during pthread_join for monitoring thread\n");

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			error_handle("Error during pthread_join for philosopher thread\n");
		i++;
	}
}

int	itadakimasu(t_philo **philo)
{
	pthread_t		*threads;
	pthread_t		checker;
	unsigned int	nb_philo;

	nb_philo = (*philo)[0].table->nb_philo;
	threads = (pthread_t *)malloc(nb_philo * sizeof(pthread_t));
	if (!threads)
		return (-1);
	if (pthread_create(&checker, NULL, monitoring, (void *)philo) != 0)
	{
		free(threads);
		return (-1);
	}
	if (create_philo_threads(threads, philo, nb_philo) != 0)
	{
		pthread_join(checker, NULL);
		free(threads);
		return (-1);
	}
	join_all_threads(checker, threads, nb_philo);
	free(threads);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_table			table;
	unsigned long	start;

	start = calculate_time();
	if (ac != 5 && ac != 6)
		return (error_handle("wrong nb of args\n"));
	if (init_table(&table, ac, av, start) == -1)
		return (error_handle("problem with one of the argument\n"));
	if (init_philo(&philo, &table) == -1)
		return (error_handle("problem with the allocation of philosophers\n"));
	if (itadakimasu(&philo) == -1)
	{
		clear_all(&philo);
		return (error_handle("failed creating threads\n"));
	}
	clear_all(&philo);
	return (0);
}
