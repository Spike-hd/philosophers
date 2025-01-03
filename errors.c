/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:25:14 by hduflos           #+#    #+#             */
/*   Updated: 2024/12/19 18:32:24 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_handle(char *error_msg) // <= il faut penser a tout free
{
	printf("%s", error_msg);
	return (-1);
}

int	is_init_correct(t_table *table)
{
	if (table->nb_philo == -1 || table->nb_philo == 0)
		return (0);
	if (table->time_to_die == -1 || table->time_to_die == 0)
		return (0);
	if (table->time_to_eat == -1 || table->time_to_eat == 0)
		return (0);
	if (table->time_to_sleep == -1 || table->time_to_sleep == 0)
		return (0);
	if (table->stop == 1)
	{
		if (table->max_meal == -1 || table->max_meal == 0)
			return (0);
	}
	return (1);
}

void	clear_all(t_philo **philo)
{
	int	i;
	int	nb_philo;
	t_table	*table;

	if (!philo || !(*philo))
		return;

	// Sauvegarder le pointeur vers la table avant de libérer `*philo`
	i = 0;
	table = (*philo)[0].table;
	nb_philo = table->nb_philo;
	while (i < nb_philo)
		pthread_mutex_destroy(&((*philo)[i++].mtx_waiting));
	free (*philo);

	pthread_mutex_destroy(&((*philo)[0].table->mtx_alive));
	pthread_mutex_destroy(&((*philo)[0].table->mtx_writing));

	if (table->chopsticks)
	{
		i = 0;
		while (i < nb_philo)
			pthread_mutex_destroy(&((*philo)[0].table->chopsticks[i++]));
		free(table->chopsticks);
	}
}
