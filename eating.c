/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:01:25 by spike             #+#    #+#             */
/*   Updated: 2024/12/20 08:44:29 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eating(void *args)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = (t_philo *)args;
	left = philo->name;
	if (philo->name == 1)
		right = philo->table->nb_philo;
	else
		right = philo->name - 1;

	if (philo->name % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->chopsticks[left]);
		pthread_mutex_lock(&philo->table->chopsticks[right]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->chopsticks[right]);
		pthread_mutex_lock(&philo->table->chopsticks[left]);
	}

}

int	itadakimasu(t_philo **philo)
{
	pthread_t		*threads;
	unsigned int	nb_philo;
	unsigned int	i;

	nb_philo = (*philo)[0].table->nb_philo;
	threads = (pthread_t *)malloc(nb_philo * sizeof(pthread_t));
	if (!threads)
		return (-1);
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(threads[i], NULL, eating, philo[i]) != 0)
			return (-1);
	}

}
