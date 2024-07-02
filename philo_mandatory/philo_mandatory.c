/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/28 16:30:25 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"


unsigned long	get_time_millisec(void)
{
	struct timeval time;
	unsigned long time_usec;
	
	gettimeofday(&time, NULL);
	
	time_usec = ((time.tv_sec * 1000000) + time.tv_usec);
	return (time_usec / 1000);
}

unsigned long	get_timestamp_millisec(unsigned long start_milli)
{
	struct timeval time;
	unsigned long time_millisec;
	
	gettimeofday(&time, NULL);
	
	time_millisec = ((time.tv_sec * 1000000) + time.tv_usec) / 1000;

	return (time_millisec - start_milli);
}



// void	print_philo(t_philo_thread *thread_n, int n, pthread_mutex_t *forks)
// {
// 	write(1,"Philo -------\n", 15);
// 	// printf("Philo\n");
// 	// pthread_mutex_lock(&thread_n->data->mtx_print);

// 	// printf("Philo #%i -> id = %li  DATA_nbr_phi -> %d\n", n, thread_n->thread_id, thread_n->data->nbr_phi);
// 	printf("Philo %i -> DATA_mtx_print -> %p\n", n, &thread_n->data->mtx_print);

// 	printf("Philo %i acces n Mutex[%i] = %p\n", n, n, &forks[n]);
// 	printf("Philo %i acces (n-1) Mutex[%i] = %p\n", n, n - 1, &forks[n - 1]);
	
// 	// pthread_mutex_unlock(&thread_n->data->mtx_print);

// }


void	print_philo(pthread_mutex_t *mtx_print, int n, long long start, char *str)
{
	pthread_mutex_lock(mtx_print);
	printf("[%li]  ", get_timestamp_millisec(start));
	printf("P%d %s\n", n, str);
	pthread_mutex_unlock(mtx_print);
}


void	*philo_do(void *thread_philo_n)
{
	t_philo_thread *thread_n;
	int n;
	pthread_mutex_t *forks;
	int counter_meals;
	// pthread_mutex_t *mtx_print_n;

	thread_n = (t_philo_thread *) thread_philo_n;
	n = thread_n->phi_num;
	forks = thread_n->data->forks;
	counter_meals = thread_n->data->nbr_meals;
	
	thread_n->last_meal = thread_n->data->start;
	// mtx_print_n = thread_n->data->mtx_print;
	int time_death = thread_n->data->t_death;
	int time_eat = thread_n->data->t_eat;
	int time_sleep = thread_n->data->t_sleep;
	int meals = thread_n->data->nbr_meals;
	unsigned long	start_simu = thread_n->data->start;
	
	int l = n - 1;
    int r =  n % thread_n->data->nbr_phi;

	// https://www.delftstack.com/fr/howto/c/gettimeofday-in-c/
	while(counter_meals != 0)
	// while(1)
	{
		if (n % 2 == 0)
		{
			pthread_mutex_lock(&forks[l]);
			print_philo(&thread_n->data->mtx_print, n, start_simu, " has taken a fork");

			pthread_mutex_lock(&forks[r]);
			print_philo(&thread_n->data->mtx_print, n, start_simu, " has taken a fork");

			thread_n->start_meal = get_time_millisec();
			if ((thread_n->start_meal - thread_n->last_meal) >= time_death)
			{
				pthread_mutex_lock(&thread_n->data->mtx_print);
				printf("XXXXXXXXXXXXXXXXXX PHILO %d *** XXXX DEAD XXXXX **** \n", n);
				pthread_mutex_unlock(&thread_n->data->mtx_print);
				free(thread_n);
				free(thread_n->data->forks);
				exit(-1);
			}

			print_philo(&thread_n->data->mtx_print, n, start_simu, " is eating");

			usleep(time_eat);
			thread_n->last_meal = thread_n->start_meal;
			pthread_mutex_unlock(&forks[r]);
			pthread_mutex_unlock(&forks[l]);

			counter_meals--;

			print_philo(&thread_n->data->mtx_print, n, start_simu, " is sleeping");

			usleep(time_sleep);

			print_philo(&thread_n->data->mtx_print, n, start_simu, " is thinking");

		}
		else if (n % 2 != 0)
		{
			pthread_mutex_lock(&forks[r]);

			print_philo(&thread_n->data->mtx_print, n, start_simu, " has taken a fork");
			
			print_philo(&thread_n->data->mtx_print, n, start_simu, " has taken a fork");

			thread_n->start_meal = get_time_millisec();

			if ((thread_n->start_meal - thread_n->last_meal) >= time_death)
			{
				pthread_mutex_lock(&thread_n->data->mtx_print);
				printf("XXXXXXXXXXXXXXXXXX PHILO %d *** XXXX DEAD XXXXX **** \n", n);
				pthread_mutex_unlock(&thread_n->data->mtx_print);
				exit (-1);
			}
			print_philo(&thread_n->data->mtx_print, n, start_simu, " is eating");

			usleep(time_eat);
			thread_n->last_meal = thread_n->start_meal;
			pthread_mutex_unlock(&forks[l]);
			pthread_mutex_unlock(&forks[r]);
			counter_meals--;

			print_philo(&thread_n->data->mtx_print, n, start_simu, " is sleeping");

			usleep(time_sleep);

			print_philo(&thread_n->data->mtx_print, n, start_simu, " is thinking");
		}
	}
	return (NULL);
}


void init_data(t_data *data)
{
	data->nbr_phi = 5;
	data->t_death = 800;
	data->t_eat= 200;
	data->t_sleep = 200;
	data->nbr_meals = 150;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_phi);
	data->start = get_time_millisec();
}

int main() 
{
	int nbr_places = 5;
	int ret;
	int i = 0;
    t_philo_thread *threads;
	t_data data;
	
	init_data(&data);
	threads = malloc(sizeof(t_philo_thread) * nbr_places);
	pthread_mutex_init(&data.mtx_print, NULL);
	// printf("Mutex mtx_print created -> %p\n", &data.mtx_print);
	while (i < nbr_places)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		// printf("Mutex #%d created -> %p\n", i, &data.forks[i]);
		i++;
	}
	// printf("--------------------------\n");
	i = 0;
    // Initialiser les threads
    while( i < nbr_places)
	{
		threads[i].phi_num = i + 1;
		threads[i].data = &data;
		threads[i].counter_meals_eaten = data.nbr_meals;
		pthread_mutex_init(&threads[i].mtx_print_philo, NULL);

		ret = pthread_create(&threads[i].thread_id, NULL, philo_do, (void *) &threads[i]);
		if (ret)
		{
			printf("ERROR; return (code from pthread_create() is %d\n", ret);
			exit(-1);
		}
		// printf("Thread #%d created -> %li\n", i, threads[i].thread_id);
		i++;
	} 
	i = 0;
	while( i < nbr_places)
    {
        pthread_join(threads[i].thread_id, NULL);
		i++;
    }
	i = 0;
	while (i < nbr_places)
	{
		 pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	free(threads);
	free(data.forks);
    // pthread_exit(NULL);
}
