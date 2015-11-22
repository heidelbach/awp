/**
 * Ersteller: Johannes Heidelbach
 *
 * implementiert sortierung
 */

#include <cstring> // memcpy
#include <cstdlib> // malloc, free

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


static void quicksort(void *const a, unsigned int const size, unsigned int const count,
		signed int (*cmp)(void *, void *))
{
	if (count <= 1)
	{
		// basic case: one element
	}
	else if (count < 24)
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

		quicksort(a, size, ptrW, cmp);
		quicksort(nextAfterPivot, size, count - ptrW - 1, cmp);
	}
}

void sort(void *const array, unsigned int size, unsigned int count, signed int (*cmp)(void *, void *))
{
	quicksort(array, size, count, cmp);
}
