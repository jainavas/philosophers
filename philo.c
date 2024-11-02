/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:45:18 by jainavas          #+#    #+#             */
/*   Updated: 2024/11/02 21:29:11 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philonew(t_philo *philos, int num)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->fork = 1;
	new->right = NULL;
	new->left = NULL;
	new->philonum = num;
	new->thread = NULL;
	pthread_create(new->thread, NULL, philo, philos);
	pthread_join(new->thread, NULL);
	return (new);
}

void	philoadd(t_philo **lst, t_philo *new)
{
	if (*lst == NULL)
		*lst = new;
	else
	{
		new->left = *lst;
		(*lst)->right = new;
	}
}

t_philo	*philolast(t_philo *lst)
{
	t_philo	*tmp;

	tmp = lst;
	if (tmp)
		while (tmp->right)
			tmp = tmp->right;
	return (tmp);
}

void	philo(t_philo philos)
{
	
}

void *thread(void *arg)
{
	printf("hola");
}

int main(int argc, char **argv)
{
	pthread_t thread1;
	t_vars		*vars;
	int	x = 0;
	int	numphilos = ft_atoi(argv[1]);

	vars = malloc(sizeof(t_vars));
	while (x++ < numphilos)
		philoadd(&vars->philos, philonew(vars->philos, x));
	vars->philos->left = philolast(vars->philos);
	vars->philos->left->right = vars->philos;
	pthread_create(&thread1, NULL, thread, &x);
}