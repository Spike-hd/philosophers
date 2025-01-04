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
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table
{
	int				nb_philo;
	pthread_mutex_t	*chopsticks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				stop;
	pthread_mutex_t	mtx_writing;
	pthread_mutex_t	mtx_alive;
	int				alive;
	int				full;
	unsigned long	start;
	int				max_meal;
}				t_table;

typedef struct s_philo
{
	int				name;
	pthread_mutex_t	mtx_waiting;
	unsigned long	waiting;
	pthread_mutex_t	mtx_dish;
	int				dish_eaten;
	t_table			*table;
}				t_philo;


//---------INIT----------------
int		init_table(t_table *table, int ac, char **av, unsigned long start);
int		init_philo(t_philo **philo, t_table *table);

// --------ERROR---------------
int		error_handle(char *error_msg);
int		is_init_correct(t_table *table);
int		clear_all(t_philo **philo);

// --------UTILS---------------
int		ft_atoi(const char *str);

// ---------THREAD------------
int		itadakimasu(t_philo **philo);
void	*monitoring(void *arg);
int		is_everyone_full(t_philo **philo, int nb_philo);
void	*eating(void *args);
int	is_everyone_alive(t_philo *philo);

// -----------TIME-------------
unsigned long	calculate_time(void);
void			init_waiting(t_philo *philo);
int				check_death(t_philo *philo);
void	ft_usleep(unsigned long time_in_ms);

// ---------LOCK-UNLOCK--------
int	sticks_lock(t_philo *philo);
void	sticks_unlock(t_philo *philo);

// -----------PRINT-------------
void	print_death(t_philo *philo);
void	print_think(t_philo *philo);
void	print_fork(t_philo *philo);
void	print_eat(t_philo *philo);
void	print_sleep(t_philo *philo);



int	test_waiting(t_philo *philo); // DEL

#endif
