/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:40:23 by jainavas          #+#    #+#             */
/*   Updated: 2024/11/04 21:40:23 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints a status message for a philosopher
 * 
 * Thread-safe printing using semaphore. Outputs timestamp, philosopher id,
 * and status message. Also updates last_meal time.
 * 
 * @param philo Pointer to the philosopher structure
 * @param status The status message to print
 */
void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	sem_wait(philo->data->print);
	timestamp = get_time_ms() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	philo->last_meal = get_time_ms();
	sem_post(philo->data->print);
}

/**
 * @brief Waits for simulation to end and terminates all processes
 * 
 * Blocks on death semaphore, then kills and waits for all child processes.
 * 
 * @param data Pointer to the simulation data structure
 */
void	wait_for_end(t_data *data)
{
	int	i;

	sem_wait(data->death);
	i = 0;
	while (i < data->num_philos)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
}

/**
 * @brief Monitors a philosopher for death or completion
 * 
 * Runs in a separate thread, checking if the philosopher has starved
 * or completed required meals. Signals death semaphore on either condition.
 * 
 * @param arg Void pointer to the philosopher structure
 * @return NULL (never returns normally)
 */
void	*death_monitor(void *arg)
{
	t_philo	*philo;
	long	time_since_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(1000);
		sem_wait(philo->data->print);
		time_since_meal = get_time_ms() - philo->last_meal;
		sem_post(philo->data->print);
		if (time_since_meal > philo->data->time_to_die)
		{
			print_status(philo, "died");
			sem_post(philo->data->death);
			exit(1);
		}
		if (philo->data->max_times_eaten != -1
			&& philo->times_eaten >= philo->data->max_times_eaten)
		{
			sem_post(philo->data->death);
			exit(0);
		}
	}
	return (NULL);
}

/**
 * @brief Handles the eating phase of a philosopher
 * 
 * Acquires two forks using semaphores, eats for the required time,
 * increments meal count, then releases both forks.
 * 
 * @param philo Pointer to the philosopher structure
 * @return 1 if max meals reached, 0 to continue
 */
int	eat(t_philo *philo)
{
	if (philo->data->max_times_eaten != -1
		&& philo->times_eaten >= philo->data->max_times_eaten)
		return (1);
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	if (philo->times_eaten != -1)
		philo->times_eaten++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (0);
}

/**
 * @brief Validates command line arguments for the simulation
 * 
 * Checks argument count, overflow conditions, and ensures all
 * values are positive integers.
 * 
 * @param argc Argument count
 * @param argv Command line arguments array
 * @return 0 if valid, -1 on error
 */
int	inputdebug(int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || checkoverflow(argv[1]) == -1
		|| checkoverflow(argv[2]) == -1 || checkoverflow(argv[3]) == -1
		|| checkoverflow(argv[4]) == -1)
		return (printf("Argumentos mal\n"), -1);
	if (argc == 6 && (checkoverflow(argv[5]) == -1 || ft_atoi(argv[5]) < 0))
		return (printf("Argumentos mal\n"), -1);
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
		return (printf("Argumentos negativos\n"), -1);
	return (0);
}
