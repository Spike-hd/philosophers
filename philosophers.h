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

typedef struct s_philo
{
	int				name;
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
	unsigned int	max_meal;

}				t_table;

//---------INIT----------------
int	init_table(t_table *table, int ac, char **av);
int	init_philo(t_philo **philo, t_table *table);

// --------ERROR---------------
int	error_handle(char *error_msg);
int	is_init_correct(t_table *table);

// --------UTILS---------------
int	ft_atoi(const char *str);

// ---------THREAD------------
int	itadakimasu(t_philo **philo);

#endif
