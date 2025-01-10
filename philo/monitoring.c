/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:07:31 by spike             #+#    #+#             */
/*   Updated: 2025/01/10 11:05:30 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo)
{
	unsigned long	now;
	unsigned long	last_meal;

	now = calculate_time();
	pthread_mutex_lock(&philo->mtx_waiting);
	last_meal = philo->waiting;
	pthread_mutex_unlock(&philo->mtx_waiting);
	if (philo->table->stop == 1)
	{
		if ((now - last_meal > (unsigned long)philo->table->time_to_die
				&& philo->dish_eaten < philo->table->max_meal)
			|| philo->table->alive == 0)
			return (1);
	}
	else
	{
		if ((now - last_meal > (unsigned long)philo->table->time_to_die)
			|| philo->table->alive == 0)
			return (1);
	}
	return (0);
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
		i = -1;
		while (++i < nb_philo)
		{
			if (check_death(&(*philo)[i]) == 1)
			{
				pthread_mutex_lock(&(*philo)[i].table->mtx_alive);
				(*philo)[i].table->alive = 0;
				pthread_mutex_unlock(&(*philo)[i].table->mtx_alive);
				print_death(&(*philo)[i]);
				return (NULL);
			}
		}
		if (is_everyone_full(philo, nb_philo) == 1)
			return (NULL);
		ft_usleep(5);
	}
	return (NULL);
}
