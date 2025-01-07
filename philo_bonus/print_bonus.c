/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <hduflos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:16:53 by hduflos           #+#    #+#             */
/*   Updated: 2025/01/07 13:57:29 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_think(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	sem_wait(philo->sem_write);
	printf("%ld Philo %d is thinking\n", time - start, philo->name);
	sem_post(philo->sem_write);
}

void	print_fork(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	sem_wait(philo->sem_write);
	printf("%ld Philo %d has taken a fork\n", time - start, philo->name);
	printf("%ld Philo %d has taken a fork\n", time - start, philo->name);
	sem_post(philo->sem_write);
}

void	print_eat(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	sem_wait(philo->sem_write);
	printf("%ld Philo %d is eating\n", time - start, philo->name);
	sem_post(philo->sem_write);
}

void	print_sleep(t_philo *philo)
{
	unsigned long	time;
	unsigned long	start;

	time = calculate_time();
	start = philo->table->start;
	sem_wait(philo->sem_write);
	printf("%ld Philo %d is sleeping\n", time - start, philo->name);
	sem_post(philo->sem_write);
}
