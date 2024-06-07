#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
int counter = 0;

void *increment_counter(void *thread_id) 
{
    long tid = (long)thread_id;
    
    // Verrouiller le mutex avant de modifier le compteur
    pthread_mutex_lock(&mutex);
    counter++;
    printf("Thread %ld incremented counter to %d\n", tid, counter);
    // Déverrouiller le mutex après avoir modifié le compteur
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

int main() 
{
    pthread_t threads[5];
    int rc;
    long t;
    
    // Initialiser le mutex
    pthread_mutex_init(&mutex, NULL);
    
    for (t = 0; t < 5; t++) 
    {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, increment_counter, (void *)t);
        
        if (rc) 
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    for (t = 0; t < 5; t++) 
    {
        pthread_join(threads[t], NULL);
    }
    
    printf("Main thread finished. Final counter value: %d\n", counter);
    
    // Détruire le mutex
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}
