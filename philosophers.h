/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:34:14 by hduflos           #+#    #+#             */
/*   Updated: 2024/12/20 08:04:29 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				name;
	pthread_mutex_t	mtx_waiting; // a faire
	unsigned int	waiting;
	int				full;
	unsigned int	dish_eaten;
	t_table			*table;
}				t_philo;

typedef struct s_table
{
	unsigned int	nb_philo;
	pthread_mutex_t	*chopsticks;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				stop;
	pthread_mutex_t	mtx_writing; // à faire
	pthread_mutex_t	mtx_alive; // à faire
	int				alive; // à faire
	unsigned int	max_meal;
}				t_table;

//---------INIT----------------
int		init_table(t_table *table, int ac, char **av);
int		init_philo(t_philo **philo, t_table *table);

// --------ERROR---------------
int		error_handle(char *error_msg);
int		is_init_correct(t_table *table);

// --------UTILS---------------
int		ft_atoi(const char *str);

// ---------THREAD------------
int		itadakimasu(t_philo **philo);
void	*monitoring(void *arg);
int		is_everyone_full(t_philo **philo, int nb_philo);
void	*eating(void *args);

// -----------TIME-------------
long	calculate_time(void);
void	init_waiting(t_philo *philo);
int		check_death(t_philo *philo);

// ---------LOCK-UNLOCK--------
void	sticks_lock(t_philo *philo);
void	sticks_unlock(t_philo *philo);

#endif
