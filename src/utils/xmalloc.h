#ifndef XMALLOC_H
#define XMALLOC_H
/**
 * \brief Function calls malloc and check the mem allocated
 *
 * \param size size to allocated
 */
void *xmalloc(size_t size);
/**
 * \brief Function calls realloc and check the mem allocated
 *
 * \param ptr pointer to realloc
 * \param size size to allocated
 */
void *xrealloc(void *ptr, size_t size);
/**
 * \brief Function calls calloc and check the mem allocated
 *
 * \param elementCount number of element to calloc
 * \param elementSize size of element to calloc
 */
void *xcalloc(size_t elementCount, size_t elementSize);

#endif /* ! XALLOC_H */
