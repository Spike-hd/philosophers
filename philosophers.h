/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spike <spike@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:34:14 by hduflos           #+#    #+#             */
/*   Updated: 2024/12/19 19:11:42 by spike            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>

typedef struct s_philo
{
	int				name;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				full;
	unsigned int	dish_eaten;

}				t_philo;

typedef struct s_table
{
	unsigned int	nb_philo;
	int				*chopsticks;
	t_philo			*philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				stop;
	unsigned int	max_meal;

}				t_table;

// --------ERROR---------------
int	error_handle(char *error_msg);
int	is_init_correct(t_table *table);

// --------UTILS---------------
int	ft_atoi(const char *str);

#endif
