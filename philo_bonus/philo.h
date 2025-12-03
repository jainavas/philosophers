/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:25:51 by jainavas          #+#    #+#             */
/*   Updated: 2025/12/03 17:04:39 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

/**
 * @brief Main data structure for the philosopher simulation (bonus version)
 * 
 * Contains all shared resources and configuration for the process-based
 * philosopher simulation using semaphores for synchronization.
 */
typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_times_eaten;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*death;
	long			start_time;
	int				sim_over;
	pid_t			*pids;
}	t_data;

/**
 * @brief Individual philosopher structure (bonus version)
 * 
 * Contains the state and configuration for each philosopher process.
 * Each philosopher runs in its own process with shared access to semaphores.
 */
typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal;
	t_data			*data;
}	t_philo;

int			ft_atoi(const char *str);
int			checkoverflow(const char *str);
int			inputdebug(int argc, char **argv);
int			init_semaphores(t_data *data);
int			create_philosophers(t_data *data);
void		philosopher_routine(t_philo *philo);
void		*death_monitor(void *arg);
int			eat(t_philo *philo);
long		get_time_ms(void);
void		ft_usleep(long ms);
void		print_status(t_philo *philo, char *status);
void		cleanup(t_data *data);
void		wait_for_end(t_data *data);

#endif