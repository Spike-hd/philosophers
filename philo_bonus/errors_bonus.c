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

#include "philo_bonus.h"

int	error_handle(char *error_msg)
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

void	close_table_sem(t_table *table)
{
	if (table->nb_pid)
		free (table->nb_pid);
	if (table->sem_forks != SEM_FAILED)
		sem_close(table->sem_forks);
	if (table->sem_done != SEM_FAILED)
		sem_close(table->sem_done);
	sem_unlink("/forks");
	sem_unlink("/done");
}

void	close_philo_sem(t_philo *philo)
{
	if (philo->sem_wait != SEM_FAILED)
		sem_close(philo->sem_wait);
	if (philo->sem_dish != SEM_FAILED)
		sem_close(philo->sem_dish);
	if (philo->sem_write != SEM_FAILED)
		sem_close(philo->sem_write);
	sem_unlink("/wait");
	sem_unlink("/dish");
	sem_unlink("/write");
}

void	clear_all(t_philo *philo)
{
	if (philo && philo->table)
	{
		close_table_sem(philo->table);
		close_philo_sem(philo);
	}
}
