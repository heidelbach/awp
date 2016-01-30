/**
 * Ersteller: Johannes Heidelbach
 *
 * implementiert sortierung
 */
#define MAX_THREADS 512
#define QSORT_TO_BUBBLESORT 32

#include <cstring> // memcpy
#include <cstdlib> // malloc, free

#include <mutex>
#include <pthread.h>

std::mutex tctl;
volatile signed int thread_count = 0;


static void swap(void *const a, void *const b, unsigned int const size)
{
	if (a != b)
	{
		void *h = malloc(size);
		memcpy(h, a, size);
		memcpy(a, b, size);
		memcpy(b, h, size);
		free(h);
	}
}

static void bubblesort(void *const a, unsigned int const size, unsigned int limit, 
		signed int (*cmp)(void *, void *))
{
	--limit;
	while (limit > 0)
	{
		unsigned int limitNew = 0;
		// remember location of last swap to shortcut
		for (unsigned int i = 0; i < limit; ++i)
		{

			void *ptr = ((void *)((unsigned long) a + i * size));
			void *ptrNext = ((void *)((unsigned long) ptr + size));
			if (cmp(ptr, ptrNext) > 0)
			{
				swap(ptr, ptrNext, size);
				limitNew = i;
			}
		}
		limit = limitNew;
	}
}

struct quicksort_args
{
  void *a;
  unsigned int size;
  unsigned int count;
  signed int (*cmp)(void *, void *);
};

static void *quicksort_child(void *const args);

static void quicksort(void *const a, unsigned int const size, unsigned int const count,
		signed int (*cmp)(void *, void *))
{
	if (count <= 1)
	{
		// basic case: one element
	}
	else if (count < QSORT_TO_BUBBLESORT)
		bubblesort(a, size, count, cmp);
	else
	{
		unsigned int const pivotPos = size * (count  / 2); // pick the one in the middle
		void *pivot = (void *)(((unsigned long) a) + pivotPos);
		void *nextAfterPivot; 
		unsigned int ptrR = 1, ptrW = 0;
		
		swap(a, pivot, size); // .. and swap it to front to be out of way pivot = a[0]
		pivot = a;	
		// all numbers left of index ptrW are less than pivot
		// index to be checked is ptrR
		
		while (ptrR < count)
		{
			void *left = (void *)(((unsigned long) a) + ptrR * size);
			if (cmp(a, left) > 0)
			{
				void *right = (void *)(((unsigned long) a) + (++ptrW * size));
				swap(right, left, size);
			}
			++ptrR;
		}
		pivot = (void *)(((unsigned long) a) + ptrW * size);
		nextAfterPivot = (void *)(((unsigned long) a) + (ptrW + 1) * size);
		swap(a, pivot, size);

    int do_fork;
    tctl.lock();
    if ( do_fork = (thread_count < MAX_THREADS) )
    {
      ++thread_count;
    }
    tctl.unlock();

    if (do_fork) 
    {
      pthread_t thread;

      // args for child
      quicksort_args *q_args=(quicksort_args *)malloc(sizeof (quicksort_args));
      q_args->a = nextAfterPivot;
      q_args->size = size;
      q_args->count = count - ptrW - 1;
      q_args->cmp = cmp;

      // create child
      if (pthread_create(&thread, NULL, quicksort_child, q_args))
      {
        // error creating child
        free(q_args);
        tctl.lock();
        --thread_count;
        tctl.unlock();
      }
      else
      {
      // do own work
      quicksort(a, size, ptrW, cmp);

      // wait for child
      pthread_join(thread, NULL);
      tctl.lock();
      --thread_count;
      tctl.unlock();
      return;
      }
    }

    // fall back, sort both partitions
		quicksort(a, size, ptrW, cmp);
		quicksort(nextAfterPivot, size, count - ptrW - 1, cmp);
	}
}

static void *quicksort_child(void *const args)
{
  quicksort_args *q_args = (quicksort_args *)args;
  quicksort(q_args->a, q_args->size, q_args->count, q_args->cmp);
  free(q_args);
  return NULL;
}


void sort(void *const array, unsigned int size, unsigned int count, signed int (*cmp)(void *, void *))
{
	quicksort(array, size, count, cmp);
}
