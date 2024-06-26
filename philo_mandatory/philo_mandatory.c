/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/26 19:49:07 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

void	print_philo(void)
{
	write(1,"Philo\n", 6);
}

void	*philo_do(void *thread_philo_n)
{
	t_philo_thread *thread_n;
	int n;
	pthread_mutex_t *forks;

	thread_n = (t_philo_thread *) thread_philo_n;
	n = thread_n->phi_num;
	forks = thread_n->data->forks;

	// write(1,"Philo\n", 6);
	// printf("Philo\n");
	// print_philo();

	printf("Philo #%i -> id = %li  DATA_nbr_phi -> %d\n", n, thread_n->thread_id, thread_n->data->nbr_phi);

	pthread_mutex_lock(&forks[n]);

	printf("Philo %i acces Mutex[n] = %p\n", n,  &forks[n]);

	// pthread_mutex_lock(&forks[n]);
	// printf("Philo %ld prends fourchette %ld\n", i, i-1);

	pthread_mutex_unlock(&forks[n]);
	// printf("Philo %ld libere fourchette %ld\n", i, i-1);
	// pthread_mutex_unlock(&mutex[i]);
	// printf("Philo %ld libere fourchette %ld\n", i, i);

	pthread_exit(NULL); //???
}

// void *increment_counter(void *thread_id) 
// {
//     long tid = (long)thread_id;
    
//     // Verrouiller le mutex avant de modifier le compteur
// 	pthread_mutex_lock(&mutex);
// 	counter++;
// 	printf("Threa #include <stdlib.h>
// d %ld incremented counter to %d\n", tid, counter);
// //     // Déverrouiller le mutex après avoir modifié le compteur
// // 	pthread_mutex_unlock(&mutex);
// //     pthread_exit(NULL);
// // }

void init_data(t_data *data)
{
	data->nbr_phi = 5;
	// data.t_death;
	// data.t_eat= 200;
	// data.t_sleep;
	data->nbr_meals = 10;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_phi);
}


int main() 
{
	int nbr_places = 5;
	int ret;
	int i = 0;

    t_philo_thread *threads;
	t_data data;
	
	init_data(&data);
	// printf("INIT DATA_nbr_phi -> %d\n", data.nbr_phi);
	threads = malloc(sizeof(t_philo_thread) * nbr_places);
	// MUTEX INI 
	while (i < nbr_places)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		printf("Mutex #%d created -> %p\n", i, &data.forks[i]);
		i++;
	}
	printf("--------------------------\n");

	i = 0;
    // Initialiser les threads
    while( i < nbr_places)
	{
		threads[i].phi_num = i + 1;
		threads[i].data = &data;
		ret = pthread_create(&threads[i].thread_id, NULL, philo_do, (void *) &threads[i]);
		if (ret)
		{
			printf("ERROR; return (code from pthread_create() is %d\n", ret);
			exit(-1);
		}
		printf("Thread #%d created -> %li\n", i, threads[i].thread_id);

		i++;
	} 
	i = 0;
	while( i < nbr_places)
    {
        pthread_join(threads[i].thread_id, NULL);
		i++;
    }
	i = 0;
	// Détruire le mutex
	while (i < nbr_places)
	{
		 pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	free(threads);
	free(data.forks);
    pthread_exit(NULL);
}
