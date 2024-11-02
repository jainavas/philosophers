/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:25:51 by jainavas          #+#    #+#             */
/*   Updated: 2024/11/02 21:10:46 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct philo
{
	int				fork;
	int				philonum;
	pthread_t 		thread;
	struct philo	*right;
	struct philo	*left;
}	t_philo;

typedef struct vars
{
	t_philo	*philos;
	int		timetodiems;
	int		timetoeatms;
	int		timetosleepms;
	int		maxtimeseaten;
}	t_vars;

int		ft_atoi(const char *str);

#endif