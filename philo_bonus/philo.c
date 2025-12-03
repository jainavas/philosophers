/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:42:27 by jainavas          #+#    #+#             */
/*   Updated: 2025/12/03 17:04:39 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Creates a new philosopher structure
 * 
 * Initializes a philosopher with the given id, meal count, last meal time,
 * and pointer to shared data.
 * 
 * @param id The philosopher's unique identifier
 * @param timeseaten Initial number of times eaten
 * @param lastmeal Timestamp of the last meal
 * @param data Pointer to shared simulation data
 * @return Initialized t_philo structure
 */
t_philo	newphilo(int id, int timeseaten, long lastmeal, t_data *data)
{
	t_philo	philo;

	philo.id = id;
	philo.times_eaten = timeseaten;
	philo.last_meal = lastmeal;
	philo.data = data;
	return (philo);
}

/**
 * @brief Initializes the semaphores used for synchronization
 * 
 * Creates three named semaphores: forks (controls fork access),
 * print (ensures atomic printing), and death (signals simulation end).
 * 
 * @param data Pointer to the simulation data structure
 * @return 0 on success, -1 on failure
 */
int	init_semaphores(t_data *data)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_death");
	data->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644,
			data->num_philos);
	if (data->forks == SEM_FAILED)
		return (-1);
	data->print = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
		return (-1);
	data->death = sem_open("/philo_death", O_CREAT | O_EXCL, 0644, 0);
	if (data->death == SEM_FAILED)
		return (-1);
	return (0);
}

/**
 * @brief Creates all philosopher processes
 * 
 * Forks child processes for each philosopher and initializes their
 * individual state. Parent stores PIDs for later cleanup.
 * 
 * @param data Pointer to the simulation data structure
 * @return 0 on success, -1 on failure
 */
int	create_philosophers(t_data *data)
{
	int		i;
	pid_t	pid;
	t_philo	philo;

	data->pids = malloc(sizeof(pid_t) * data->num_philos);
	if (!data->pids)
		return (-1);
	data->start_time = get_time_ms();
	i = 0;
	while (i < data->num_philos)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
		{
			philo = newphilo(i + 1, 0, data->start_time, data);
			philosopher_routine(&philo);
			exit(0);
		}
		data->pids[i] = pid;
		i++;
	}
	return (0);
}

/**
 * @brief The main routine each philosopher process executes
 * 
 * Handles the philosopher's lifecycle of eating, sleeping, and thinking.
 * Spawns a death monitor thread and loops until simulation ends.
 * 
 * @param philo Pointer to the philosopher structure
 */
void	philosopher_routine(t_philo *philo)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, death_monitor, philo);
	pthread_detach(monitor);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (eat(philo))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
	}
}

/**
 * @brief Main entry point for the philosophers simulation
 * 
 * Validates input, creates philosopher structures, runs the simulation,
 * and handles cleanup afterward.
 * 
 * @param argc Argument count
 * @param argv Command line arguments
 * @return 0 on success, -1 on error
 */
int	main(int argc, char **argv)
{
	t_data	data;

	if (inputdebug(argc, argv) == -1)
		return (-1);
	data.num_philos = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.max_times_eaten = ft_atoi(argv[5]);
	else
		data.max_times_eaten = -1;
	if (init_semaphores(&data) == -1)
		return (-1);
	if (create_philosophers(&data) == -1)
		return (-1);
	wait_for_end(&data);
	cleanup(&data);
	return (0);
}
