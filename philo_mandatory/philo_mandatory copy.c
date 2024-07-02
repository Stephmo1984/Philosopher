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



void	print_philo(t_philo_thread *thread_n, int n, pthread_mutex_t *forks)
{
	write(1,"Philo -------\n", 15);
	// printf("Philo\n");
	// pthread_mutex_lock(&thread_n->data->mtx_print);

	// printf("Philo #%i -> id = %li  DATA_nbr_phi -> %d\n", n, thread_n->thread_id, thread_n->data->nbr_phi);
	printf("Philo %i -> DATA_mtx_print -> %p\n", n, &thread_n->data->mtx_print);

	printf("Philo %i acces n Mutex[%i] = %p\n", n, n, &forks[n]);
	printf("Philo %i acces (n-1) Mutex[%i] = %p\n", n, n - 1, &forks[n - 1]);
	
	// pthread_mutex_unlock(&thread_n->data->mtx_print);

}

void	*philo_do(void *thread_philo_n)
{
	t_philo_thread *thread_n;
	int n;
	pthread_mutex_t *forks;
	int counter_meals;

	thread_n = (t_philo_thread *) thread_philo_n;
	n = thread_n->phi_num;
	forks = thread_n->data->forks;
	counter_meals = thread_n->data->nbr_meals;
	
	// printf("***TIME**** DATA_START = %li\n", thread_n->data->start);
	thread_n->last_meal = thread_n->data->start;
	
	// int time_death = thread_n->data->t_death;
	int time_eat = thread_n->data->t_eat;
	int time_sleep = thread_n->data->t_sleep;
	int meals = thread_n->data->nbr_meals;
	
	int l = n - 1;
    int r =  n % thread_n->data->nbr_phi;

	// https://www.delftstack.com/fr/howto/c/gettimeofday-in-c/
	//while(counter_meals != 0) 
	while(1)
	{
		if (n % 2 == 0)
		{
			pthread_mutex_lock(&thread_n->data->mtx_print);
			write(1,"--------------\n", 15);
			if(counter_meals == thread_n->data->nbr_meals)
				printf("PHILO %d ***TIME**** LAST_MEAL_INIT = %li\n --------------\n", n, thread_n->last_meal);
			printf("Philosopher %d is thinking.\n", n);
			
			pthread_mutex_lock(&forks[l]);
			printf("Philosopher %d picked L fork (%i) %p.\n", n, n, &forks[l]);

			pthread_mutex_lock(&forks[r]);
			printf("Philosopher %d picked R fork (%i) %p.\n", n, n-1, &forks[r]);
			
			thread_n->start_meal = get_time_millisec();
			printf("***TIME PHILO_START_MEAL from last meal****  = %li\n", thread_n->start_meal - thread_n->last_meal);
			if ((thread_n->start_meal - thread_n->last_meal) >= thread_n->data->t_death)
			{
				printf("XXXXXXXXXXXXXXXXXX PHILO %d *** XXXX DEAD XXXXX **** \n", n);

				exit(-1);
			}
			printf("Philosopher %d is eating.\n", n);	

			usleep(time_eat);
			thread_n->last_meal = thread_n->start_meal;
			
			pthread_mutex_unlock(&forks[r]);
			printf("Philosopher %d put down R fork (%i) %p.\n", n, n - 1, &forks[r]);

			pthread_mutex_unlock(&forks[l]);
			printf("Philosopher %d put down L fork (%i) %p.\n", n, n, &forks[l]);
			
			counter_meals--;

			printf("Philosopher %d is sleeping.\n", n);
			usleep(time_sleep);

			pthread_mutex_unlock(&thread_n->data->mtx_print);
		}
		else if (n % 2 != 0)
		{
			pthread_mutex_lock(&thread_n->data->mtx_print);
			write(1,"--------------\n", 15);
			if(counter_meals == thread_n->data->nbr_meals)
				printf("/////////////// PHILO %d ***TIME**** LAST_MEAL_INIT = %li\n --------------\n", n, thread_n->last_meal);

			printf("Philosopher %d is thinking.\n", n);
			
			pthread_mutex_lock(&forks[r]);
			printf("Philosopher %d picked R fork (%i) %p.\n", n, n-1, &forks[r]);
			
			pthread_mutex_lock(&forks[l]);
			printf("Philosopher %d picked L fork (%i) %p.\n", n, n, &forks[l]);
						
			thread_n->start_meal = get_time_millisec();
			printf("***TIME PHILO_START_MEAL from last meal**** = %li\n", thread_n->start_meal - thread_n->last_meal);
			if ((thread_n->start_meal - thread_n->last_meal) >= thread_n->data->t_death)
			{
				printf("XXXXXXXXXXXXXXXXXX PHILO %d *** XXXX DEAD XXXXX **** \n", n);
				exit (-1);
			}
			printf("Philosopher %d is eating.\n", n);	
			usleep(time_eat);
			thread_n->last_meal = thread_n->start_meal;
			
			pthread_mutex_unlock(&forks[l]);
			printf("Philosopher %d put down L fork (%i) %p.\n", n, n, &forks[l]);
			
			pthread_mutex_unlock(&forks[r]);
			printf("Philosopher %d put down R fork (%i) %p.\n", n, n - 1, &forks[r]);

			counter_meals--;

			printf("Philosopher %d is sleeping.\n", n);
			usleep(time_sleep);

			pthread_mutex_unlock(&thread_n->data->mtx_print);
		}
	}
	pthread_exit(NULL); //???
	// exit (1);
}


void init_data(t_data *data)
{
	data->nbr_phi = 5;
	data->t_death = 102;
	data->t_eat= 200;
	data->t_sleep = 200;
	data->nbr_meals = 7;
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
    pthread_exit(NULL);
}
