/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:25:51 by jainavas          #+#    #+#             */
/*   Updated: 2024/12/10 01:20:21 by jainavas         ###   ########.fr       */
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

typedef struct control
{
	pthread_mutex_t	lock;
	int				sim_over;
	int				dontprint;
}	t_sim;

typedef struct time
{
	pthread_mutex_t	lock;
	int				x;
	int				c;
}	t_timec;

typedef struct philo
{
	int				philosall;
	int				philonum;
	int				dead;
	pthread_t		thread;
	pthread_mutex_t	lock;
	struct philo	*right;
	struct philo	*left;
	t_timec			*time;
	int				timetodiems;
	int				timetoeatms;
	int				timetosleepms;
	int				maxtimeseaten;
	t_sim			*sim;
	int				f;
}	t_philo;

int			ft_atoi(const char *str);
long int	timeinms(struct timeval *tv, t_philo *philo);
int			checksim(t_philo *philo);
int			getforkeven(t_philo *philo, struct timeval *tv);
int			getforkodd(t_philo *philo, struct timeval *tv);
void		philoinit(t_philo *philo, char **argv, t_sim *control);
t_philo		*philolast(t_philo *lst);
void		*philo_routine(void *philo);
void		philonew(t_philo **philos, int num, int numphilos);
void		freephilos(t_philo **philos, int nphilos);
int			eat(t_philo *philo, struct timeval *tv);
int			checkoverflow(const char *str);
int			inputdebug(int argc, char **argv);
int			routinewhile(t_philo *philo, struct timeval *tv);
int			bettersleep(long mstosleep, t_philo *philo);
void		putsimovr(t_philo *philo);

#endif