#include <stdio.h>
#include <pthread.h>

struct shared
{
   int data;
   pthread_mutex_t mut;
};

struct data
{
 
   int nb;  /* paramètre */
   char const *sid;   /* paramètre */
   struct shared *psh; /* contexte partage' */
};

static void *task_w (void *p)
{
   if (p != NULL)
   {
      struct data *p_data = p;
      int i;
	  int x = p_data->psh->data;

      for (i = 0; i < p_data->nb; i++)
      {
         pthread_mutex_lock (&p_data->psh->mut);
         {
            x++;
            p_data->psh->data = x;
         }
         printf ("'%s' (%d) data <- %d\n", p_data->sid, i, p_data->psh->data);
         pthread_mutex_unlock (&p_data->psh->mut);
      }
   }
   return NULL;
}

static void *task_r (void *p)
{
   if (p != NULL)
   {
      struct data *p_data = p;
      int i;

      for (i = 0; i < p_data->nb; i++)
      {
         pthread_mutex_lock (&p_data->psh->mut);
         printf ("                        "
               "'%s' (%d) data == %d\n", p_data->sid, i, p_data->psh->data);
         pthread_mutex_unlock (&p_data->psh->mut);
      }
   }
   return NULL;
}

int main (void)
{
   pthread_t thread_1;
   pthread_t thread_2;

   struct shared sh =
   {
      .data = 10,
      .mut = PTHREAD_MUTEX_INITIALIZER,
   };

   struct data data_a =
   {
      .nb = 5,
      .sid = "Writer",
      .psh = &sh,
   };

   struct data data_b =
   {
      .nb = 7,
      .sid = "Reader",
      .psh = &sh,
   };

   puts ("main init");

   pthread_create (&thread_1, NULL, task_w, &data_a);
   pthread_create (&thread_2, NULL, task_r, &data_b);

   pthread_join (thread_1, NULL);
   pthread_join (thread_2, NULL);

   puts ("main end");

   return 0;
}