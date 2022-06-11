#ifndef _MAXHEAP_H
#define _MAXHEAP_H

typedef int key_type;
typedef struct _maxheap *maxheap;

maxheap maxheap_create();
maxheap maxheap_heapify(const key_type *array, int n);
void maxheap_destroy(maxheap);

int maxheap_findmax(maxheap);
void maxheap_insert(maxheap, key_type);
void maxheap_deletemax(maxheap);

int maxheap_is_empty(maxheap);
int maxheap_size(maxheap);
void maxheap_clear(maxheap);

#endif
