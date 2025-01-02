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

int	itadakimasu(t_philo **philo)
{
	pthread_t		*threads;
	pthread_t		checker;
	unsigned int	nb_philo;
	unsigned int	i;

	nb_philo = (*philo)[0].table->nb_philo;
	threads = (pthread_t *)malloc(nb_philo * sizeof(pthread_t));
	if (!threads)
		return (-1);
	if (pthread_create(&checker, NULL, monitoring, (void *)philo) != 0)
			return (-1);
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&threads[i], NULL, eating, (void *)&((*philo)[i])) != 0)
			return (error_pthread(i, threads)); // pb avec le checker maybe géré dans le main ?
	}
	pthread_join(checker, NULL);
	i = -1;
	while (++i < nb_philo)
		pthread_join(threads[i], NULL);
	free(threads);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_table	table;

	if (ac != 5 && ac != 6)
		return (error_handle("wrong nb of args\n"));
	if (init_table(&table, ac, av) == -1)
		return (error_handle("problem with one of the argument\n"));
	if (init_philo(&philo, &table) == -1)
		return (error_handle("problem with the allocation of philosophers\n"));

}
