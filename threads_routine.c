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

int	is_everyone_alive(t_philo *philo)
{
	// Vérifie si la table est "vivante"
	pthread_mutex_lock(philo->table->mtx_alive);
	if (philo->table->alive == 0)
	{
		pthread_mutex_unlock(philo->table->mtx_alive);
		return (0);
	}
	pthread_mutex_unlock(philo->table->mtx_alive);
	return (1);
}

int	eating_routine(t_philo *philo, int left, int right, int max_dish)
{
	while (philo->dish_eaten < max_dish)
	{
		// Philosophe commence à réfléchir
		if (is_everyone_alive(philo) == 0)
			return (-1);
		init_waiting(philo);
		print_think(philo); // THINK

		// Philosophe commence à manger
		sticks_lock(philo);
		if (is_everyone_alive(philo) == 0)
			return (-1);
		print_eat(philo); // EAT
		sticks_unlock(philo);

		// Philosophe dort
		if (is_everyone_alive(philo) == 0)
			return (-1);
		print_sleep(philo); // SLEEP

		// Incrémente le compteur de repas
		philo->dish_eaten++;
	}
	return (0); // Philosophe a terminé son cycle normal
}

void	*eating(void *args)
{
	t_philo	*philo;
	int		left;
	int		right;
	int		max_dish;

	philo = (t_philo *)args;
	left = philo->name;
	if (philo->name == 1)
		right = philo->table->nb_philo;
	else
		right = philo->name - 1;

	if (philo->table->stop == 0)
		max_dish = philo->dish_eaten + 1;
	else
		max_dish = philo->table->max_meal;
	eating_routine(philo, left, right, max_dish);
}

int	is_everyone_full(t_philo **philo, int nb_philo)
{
	int	j;

	j = 0;
	if ((*philo)[j].table->stop == 0)
		return (0);
	while (j < nb_philo)
	{
		if ((*philo)[j].dish_eaten < (*philo)[j].table->max_meal)
			break;
		j++;
	}
	if (j == nb_philo)
		return (1);
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	**philo;
	int		nb_philo;
	int		i;

	philo = (t_philo **)arg;
	nb_philo = (*philo)[0].table->nb_philo;
	while (1)
	{
		i = 0;
		while (i < nb_philo)
		{
			if (check_death((*philo)[i]) == 1)
			{
				pthread_mutex_lock((*philo)[i].table->mtx_alive);
				(*philo)[i].table->alive = 0;
				pthread_mutex_unlock((*philo)[i].table->mtx_alive);
				print_death((*philo)[i]);
				return (NULL);
			}
			i++;
		}
		if (is_everyone_full(philo, nb_philo) == 1)
				return (NULL);
	}
	return (NULL);
}
