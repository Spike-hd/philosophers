/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:26:17 by marvin            #+#    #+#             */
/*   Updated: 2025/01/05 16:26:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_table
{
	int				nb_philo;
	int				*nb_pid;
	sem_t			*sem_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				stop;
	int				max_meal;
	sem_t			sem_done;
	unsigned long	start;
}				t_table;

typedef struct s_philo
{
	int				name;
	sem_t			sem_wait;
	unsigned long	last_meal;
	sem_t			sem_dish;
	sem_t			sem_write;
	int				dish_eaten;
	t_table			*table;
}				t_philo;

#endif
