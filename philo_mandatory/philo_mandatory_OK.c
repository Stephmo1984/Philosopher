/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory_OK.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:12:56 by smortemo          #+#    #+#             */
/*   Updated: 2024/07/12 11:48:34 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "struct.h"

// t_bool	get_value_bool(pthread_mutex_t *mtx, t_bool to_get)
// {
// 	t_bool	value;
// 	pthread_mutex_lock(mtx);
// 	value = to_get;
// 	// write(1, "t_bool updated\n", 16);
// 	pthread_mutex_unlock(mtx);
// 	return (value);
// }

void	set_value_bool(pthread_mutex_t *mtx, t_bool to_modify, t_bool value)
{
	pthread_mutex_lock(mtx);
	to_modify = value;
	pthread_mutex_unlock(mtx);
}
void	set_value_unlong(pthread_mutex_t *mtx, unsigned long to_modify, unsigned long value)
{
	pthread_mutex_lock(mtx);
	to_modify = value;
	pthread_mutex_unlock(mtx);
}

void	philo_eat(t_philo_thread *thread_n, pthread_mutex_t *forks, int fisrt_fork, int second_fork)
{
	unsigned long meal_start;
	
	meal_start = get_timestamp_millisec(thread_n->data->start);
	thread_n->last_meal = thread_n->start_meal;
	thread_n->start_meal = meal_start;//set_get
	// set_value_unlong(&thread_n->mtx_time, thread_n->start_meal, meal_start);//
	print_philo(&thread_n->data->mtx_print, thread_n->phi_num, thread_n->data->start, " is eating");
	usleep(thread_n->data->t_eat * 1000);
	pthread_mutex_unlock(&forks[second_fork]);
	pthread_mutex_unlock(&forks[fisrt_fork]);
}


void *philo_is_dead(void *thread_philo)
{
	t_philo_thread *thread;
	unsigned long death;
	unsigned long diff;
	unsigned long time_stamp;
	int nbr_phi;
	int i;
	int count;
	
	time_stamp = 0;
	count = 0;
	thread = (t_philo_thread *) thread_philo;	
	death = thread->data->t_death;
	i = 0;
	nbr_phi = thread->data->nbr_phi;
	
	while(1)
	{
		while (i < nbr_phi)
		{
			if (thread[i].is_full == TRUE)
			{
				i++;
				count++;
				if (count == nbr_phi - 1)
					return(NULL);
			}
			else
			{
				time_stamp = get_timestamp_millisec(thread[i].start_simu);
				diff = time_stamp - (thread[i].start_meal);//set_get
				if (diff > death)
				{
					print_philo(&thread->data->mtx_print, thread[i].phi_num, thread->data->start, " PHILOSOPHER IS DEAD");	
					thread->data->one_dead = TRUE;
					return(NULL);
				}	
			}
		}
		usleep(5000);
		i = 0;
	}
	return(thread_philo);
}


void	*philo_do_even(void *thread_philo_n)
{
	t_philo_thread *thread_n;
	int n;
	pthread_mutex_t *forks;
	int counter_meals;
	int l;
	int r;

	thread_n = (t_philo_thread *) thread_philo_n;
	n = thread_n->phi_num;
	forks = thread_n->data->forks;
	counter_meals = thread_n->data->nbr_meals;
	thread_n->last_meal = 0;
	thread_n->start_meal = 0;

	l = n - 1;
	r =  n % thread_n->data->nbr_phi;
	while(1)
	{
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is thinking");
			pthread_mutex_lock(&forks[l]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			pthread_mutex_lock(&forks[r]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			philo_eat(thread_n, forks, l, r);
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			if (thread_n->meals_are_limited == TRUE)
				counter_meals--;
			if(counter_meals == 0)
			{
				thread_n->is_full = TRUE;
				print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " PHILOSOPHER IS FULL");
				return (NULL);
			}
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
	}
	return (NULL);
}

void	*philo_do_odd(void *thread_philo_n)
{
	t_philo_thread *thread_n;
	int n;
	pthread_mutex_t *forks;
	int counter_meals;
	int l;
	int r;

	thread_n = (t_philo_thread *) thread_philo_n;
	n = thread_n->phi_num;
	forks = thread_n->data->forks;
	counter_meals = thread_n->data->nbr_meals;
	thread_n->last_meal = 0;
	thread_n->start_meal = 0;

	l = n - 1;
	r =  n % thread_n->data->nbr_phi;
	while(1)
	{
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is thinking");
			pthread_mutex_lock(&forks[r]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			pthread_mutex_lock(&forks[l]);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " has taken a fork");
			philo_eat(thread_n, forks, r, l);
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			if (thread_n->meals_are_limited == TRUE)
				counter_meals--;
			if(counter_meals == 0)
			{
				thread_n->is_full = TRUE;
				print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " PHILOSOPHER IS FULL");
				return (NULL);
			}
			if(thread_n->data->one_dead == TRUE)
				return(NULL);
			print_philo(&thread_n->data->mtx_print, n, thread_n->data->start, " is sleeping");
			usleep(thread_n->data->t_sleep * 1000);
	}
	return (NULL);
}

void init_data(t_data *data, char **argv)
{
	philo_check_args(argv);

	data->nbr_meals = 1;
	data->meals_number = FALSE;
	data->nbr_phi = ft_atoi_philo(argv[1]);
	if (data->nbr_phi > 124098)
		exit_error_message("Too many threads (philosophers) -> to see max threads value: cat /proc/sys/kernel/threads-max\n"); //         cat /proc/sys/kernel/threads-max       
	data->t_death =  ft_atol_unsigned_philo(argv[2]);
	data->t_eat=  ft_atol_unsigned_philo(argv[3]);
	data->t_sleep =  ft_atol_unsigned_philo(argv[4]);
	if (argv[5])
	{
		data->nbr_meals =  ft_atoi_philo(argv[5]);
		data->meals_number = TRUE;
	}	
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_phi);
	data->one_dead = FALSE;
	data->start = get_time_millisec();
}

void	init_philo(t_data *data, t_philo_thread *threads)
{
	int i;

	i = 0;
	while( i < data->nbr_phi )
	{
			threads[i].one_dead = &data->one_dead;
			threads[i].meals_are_limited = data->meals_number;
			threads[i].is_full = FALSE;
			threads[i].phi_num = i + 1;
			threads[i].data = data;
			threads[i].start_simu = data->start;
			threads[i].counter_meals_eaten = data->nbr_meals;
			threads[i].last_meal = data->start;
			i++;
	}
}

void	init_thread(t_data *data, t_philo_thread *threads)
{
	int ret;
	int i;
	
	init_philo(data, threads);
	i = 0;
	while( i < data->nbr_phi )
	{
			if( (i + 1) % 2 == 0)
			{
				ret = pthread_create(&threads[i].thread_id, NULL, philo_do_even, (void *) &threads[i]);
				if (ret)
					exit_error_message("ERROR: pthread_create()\n");
			}
			else
			{
				usleep(1000);
				ret = pthread_create(&threads[i].thread_id, NULL, philo_do_odd, (void *) &threads[i]);
				if (ret)
					exit_error_message("ERROR: pthread_create()\n");
			}
			i++;
	}
}

void	join_and_destroy(t_data *data, t_philo_thread *threads)
{
	int i;

	i = 0;
	while( i < data->nbr_phi)
    {
        pthread_join(threads[i].thread_id, NULL);
		i++;
	}
	while (i < data->nbr_phi)
	{
		 pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mtx_print);
	// pthread_mutex_destroy(&data->mtx_death);
}



int main(int argc, char **argv) 
{
	int nbr_of_chairs;
	int i;
    t_philo_thread *threads;
	t_data data;
	
	if (argc > 6)
		exit_error_message("Too many args\n");
	init_data(&data, argv);
	nbr_of_chairs = data.nbr_phi;
	threads = malloc(sizeof(t_philo_thread) * nbr_of_chairs);
	pthread_mutex_init(&data.mtx_print, NULL);
	// pthread_mutex_init(&data.mtx_death, NULL);//
	init_mutex(&data);
	init_thread(&data, threads);
	philo_is_dead(threads);
	join_and_destroy(&data, threads);
	free(threads);
	free(data.forks);
	return (0);
}
