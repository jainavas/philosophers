/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:25:51 by jainavas          #+#    #+#             */
/*   Updated: 2024/11/06 19:10:18 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct philo
{
	int				philosall;
	int				philonum;
	pthread_t		thread;
	pthread_mutex_t	lock;
	struct philo	*right;
	struct philo	*left;
	int				timetodiems;
	int				timetoeatms;
	int				timetosleepms;
	int				maxtimeseaten;
}	t_philo;

int		ft_atoi(const char *str);
t_philo	*philolast(t_philo *lst);
void	*philo_routine(void *philo);
void	philonew(t_philo **philos, int num, int numphilos);
void	freephilos(t_philo **philos, int nphilos);
void	eat(t_philo *philo, struct timeval *tv, int x, int c);
int		checkoverflow(const char *str);
int		inputdebug(int argc, char **argv);

#endif