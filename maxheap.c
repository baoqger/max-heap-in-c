#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "maxheap.h"


struct _maxheap {
	key_type* array;
	int max_size;
	int cur_size;
};

maxheap maxheap_create() {
	maxheap h = (maxheap)malloc(sizeof(struct _maxheap));
	if (h == NULL) {
		fprintf(stderr, "Not enough memory!\n");
		abort();
	}
	h->max_size = 64;
	h->cur_size = -1;
	h->array = (key_type*) malloc(sizeof(key_type)*(h->max_size));
	if (h->array == NULL) {
		fprintf(stderr, "Not enough memory!\n");
		abort();
	}
	return h;
}

void maxheap_destroy(maxheap h) {
	assert(h);
	free(h->array);
	free(h);
}


static void maxheap_double_capacity(maxheap h) {
	int new_max_size = 2 * h->max_size;
	key_type* new_array = (key_type*) malloc(sizeof(key_type)* (new_max_size));

	if (new_array == NULL) {
		fprintf(stderr, "Not enough memory!\n");
		abort();
	}
	for(int i = 0; i < h->cur_size; i++) {
		new_array[i] = h->array[i];
	}
	free(h->array);
	h->array = new_array;
	h->max_size = new_max_size;
}

static void maxheap_swap(maxheap h, int i, int j) {
	assert(h && i >=0 && i <= h->cur_size && j >= 0 && j <= h->cur_size);
	key_type tmp = h->array[i];
	h->array[i] = h->array[j];
	h->array[j] = tmp;
}


static void maxheap_heapifyup(maxheap h, int k) {
	assert(h && k >= 0 && k <= h->cur_size);

	while(k>=0 && h->array[k] > h->array[k/2]) {
		maxheap_swap(h, k/2, k);
		k /= 2;
	}
}

static void maxheap_heapifydown(maxheap h, int k) {
	assert(h);
	
	while(2*k <= h->cur_size) {
		int j = 2*k;
		if (j<h->cur_size && h->array[j+1] > h->array[j]) {
			j++;
		}
		if (h->array[k] >= h->array[j]) {
			break;
		}
		maxheap_swap(h, k, j);
		k = j;
	}
}

void maxheap_insert(maxheap h, key_type key) {
	assert(h);

	h->cur_size += 1;
	// make sure there is space
	if (h->cur_size == h->max_size) {
		maxheap_double_capacity(h);
	}

	// add at the end
	h->array[h->cur_size] = key;
	
	// restore the heap property by heapify-up
	maxheap_heapifyup(h, h->cur_size);

}

int maxheap_findmax(maxheap h) {
	if (maxheap_is_empty(h)) {
		fprintf(stderr, "Heap is empty!\n");
		abort();
	}

	// max is the first position
	return h->array[0];
}

void maxheap_deletemax(maxheap h) {
	if (maxheap_is_empty(h)) {
		fprintf(stderr, "Heap is empty!\n");
		abort();
	}
	// swap the first and last element
	maxheap_swap(h, 0, h->cur_size);
	h->cur_size -= 1;
	
	maxheap_heapifydown(h, 0);
}


int maxheap_size(maxheap h) {
	assert(h);
	return h->cur_size;
}

int maxheap_is_empty(maxheap h) {
	assert(h);
	return h->cur_size < 0;
}

void maxheap_clear(maxheap h) {
	assert(h);
	h->cur_size = -1;
}


maxheap maxheap_heapify(const key_type* array, int n) {
	assert(array && n > 0);
	
	maxheap h = (maxheap)malloc(sizeof(struct _maxheap));
	if(h == NULL) {
		fprintf(stderr, "Not enough memory!\n");
		abort();
	}
	h->max_size = n;
	h->cur_size = -1;
	h->array = (key_type*)(malloc(sizeof(key_type)*h->max_size));
	if(h->array == NULL) {
		fprintf(stderr, "Not enough memory!\n");
		abort();
	}
	h->cur_size = n-1;
	for (int i=0; i< n; i++) {
		h->array[i] = array[i];
	}
	for (int i = h->max_size/2; i >= 0; i--) {
		maxheap_heapifydown(h, i);
	}
	return h;
}

int main() {
	int i;
	srand(time(NULL));
	
	maxheap h = maxheap_create();

	for (i=0; i<100; i++) {
		maxheap_insert(h, i);
	}

	while(!maxheap_is_empty(h)){
		printf("%4d", maxheap_findmax(h));
		maxheap_deletemax(h);
	} 
	maxheap_destroy(h);
	return 0;
}


