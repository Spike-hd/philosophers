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
	pthread_mutex_lock(&philo->table->mtx_alive);
	if (philo->table->alive == 0)
	{
		pthread_mutex_unlock(&philo->table->mtx_alive);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->mtx_alive);
	return (1);
}

int	eating_routine(t_philo *philo, int max_dish)
{
	if (is_everyone_alive(philo) == 0)
			return (-1);
	while (philo->dish_eaten < max_dish)
	{
		// Philosophe commence à réfléchir
		if (is_everyone_alive(philo) == 0)
			return (-1);
		print_think(philo); // THINK

		// Philosophe commence à manger
		if (is_everyone_alive(philo) == 0)
			return (-1);
		if (sticks_lock(philo) == -1)
			return (-1);
		print_eat(philo); // EAT
		ft_usleep(philo->table->time_to_eat);
		sticks_unlock(philo);
		init_waiting(philo);

		// Philosophe dort
		if (is_everyone_alive(philo) == 0)
			return (-1);
		print_sleep(philo); // SLEEP
		ft_usleep(philo->table->time_to_sleep);

		pthread_mutex_lock(&philo->mtx_dish);
		if (philo->table->stop == 1)
			philo->dish_eaten++;
		pthread_mutex_unlock(&philo->mtx_dish);
	}
	return (0); // Philosophe a terminé son cycle normal
}

void	*eating(void *args)
{
	t_philo	*philo;
	int		max_dish;

	philo = (t_philo *)args;
	if (philo->table->stop == 0)
		max_dish = philo->dish_eaten + 1;
	else
		max_dish = philo->table->max_meal;
	eating_routine(philo, max_dish);
	return (NULL);
}

int	is_everyone_full(t_philo **philo, int nb_philo)
{
	int	j;

	j = 0;
	if ((*philo)[j].table->stop == 0)
		return (0);
	while (j < nb_philo)
	{
		pthread_mutex_lock(&(*philo)[j].mtx_dish);
		if ((*philo)[j].dish_eaten < (*philo)[j].table->max_meal)
		{
			pthread_mutex_unlock(&(*philo)[j].mtx_dish);
			return (0);
		}
		pthread_mutex_unlock(&(*philo)[j].mtx_dish);
		j++;
	}
	printf("Everyone ate %d times !", (*philo)[0].table->max_meal);
	return (1);
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
			if (check_death(&(*philo)[i]) == 1)
			{
				pthread_mutex_lock(&(*philo)[i].table->mtx_alive);
				(*philo)[i].table->alive = 0;
				pthread_mutex_unlock(&(*philo)[i].table->mtx_alive);
				print_death(&(*philo)[i]);
				return (NULL);
			}
			i++;
		}
		if (is_everyone_full(philo, nb_philo) == 1)
				return (NULL);
		ft_usleep(10);
	}
	return (NULL);
}
