/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:25:51 by jainavas          #+#    #+#             */
/*   Updated: 2025/05/11 20:58:12 by jainavas         ###   ########.fr       */
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

/**
 * @brief Simulation control structure shared between all philosophers
 * 
 * Contains thread-safe flags to control the simulation state and printing.
 */
typedef struct control
{
    pthread_mutex_t	lock;      // Mutex to protect access to the struct fields
    int				sim_over;  // Flag indicating if simulation should end
    int				dontprint; // Flag to control message printing
}	t_sim;

/**
 * @brief Structure to track simulation timing
 * 
 * Stores the start time of the simulation to calculate elapsed time.
 */
typedef struct time
{
    pthread_mutex_t	lock;      // Mutex to protect access to time values
    int				x;         // Microseconds part of start time
    int				c;         // Seconds part of start time
}	t_timec;

/**
 * @brief Philosopher structure representing each dining philosopher
 * 
 * Contains all state data and settings for an individual philosopher,
 * including their timing parameters, neighbor connections, and thread.
 */
typedef struct philo
{
    int				philosall;     // Total number of philosophers in simulation
    int				philonum;      // This philosopher's ID number
    int				dead;          // Flag if this philosopher has died
    pthread_t		thread;        // Thread for this philosopher's routine
    pthread_mutex_t	lock;          // Mutex representing this philosopher's fork
    struct philo	*right;        // Pointer to right neighbor philosopher
    struct philo	*left;         // Pointer to left neighbor philosopher
    t_timec			*time;         // Pointer to shared time structure
    int				timetodiems;   // Time until philosopher dies of starvation (ms)
    int				timetoeatms;   // Time it takes philosopher to eat (ms)
    int				timetosleepms; // Time it takes philosopher to sleep (ms)
    int				maxtimeseaten; // Maximum number of times to eat
    t_sim			*sim;          // Pointer to shared simulation control
    int				f;             // Time of last meal (ms since start)
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