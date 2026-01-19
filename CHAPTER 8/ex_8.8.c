/*Write a routine bfree(p,n) that will free any arbitrary block p of n characters
into the free list maintained by malloc and free. By using bfree, a user can add a static or
external array to the free list at any time.*/

#include <stdio.h>
#include <unistd.h>

#define NALLOC 1024

typedef long Align;

/* block header */
union header {
    struct {
        union header *ptr;  /* next block in free list */
        unsigned size;      /* size in Header units */
    } s;
    Align x;               /* force alignment */
};

typedef union header Header;

static Header base;              /* empty list to get started */
static Header *freep = NULL;     /* start of free list */

static Header *morecore(unsigned);

/* free: put block ap in free list */
void _free(void *ap)
{
    Header *bp, *p;

    if (ap == NULL)
        return;

    if (freep == NULL) {
        base.s.ptr = &base;
        base.s.size = 0;
        freep = &base;
    }

    bp = (Header *)ap - 1;

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;

    freep = p;
}

/* malloc: general-purpose storage allocator */
void *_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    if (nbytes == 0)
        return NULL;

    if (freep == NULL) {
        base.s.ptr = &base;
        base.s.size = 0;
        freep = &base;
    }

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    prevp = freep;

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)
        return NULL;

    up = (Header *)cp;
    up->s.size = nu;
    _free((void *)(up + 1));
    return freep;
}

/* bfree: add arbitrary memory to free list */
unsigned bfree(char *p, unsigned n)
{
    Header *hp;

    if (n < sizeof(Header))
        return 0;

    if (freep == NULL) {
        base.s.ptr = &base;
        base.s.size = 0;
        freep = &base;
    }

    hp = (Header *)p;
    hp->s.size = n / sizeof(Header);
    _free((void *)(hp + 1));
    return hp->s.size;
}

/* test */
int main(void)
{
    static char buffer[4096];

    printf("Adding static buffer via bfree...\n");
    bfree(buffer, sizeof(buffer));

    char *p = _malloc(100);
    char *q = _malloc(200);

    printf("Allocated p = %p\n", p);
    printf("Allocated q = %p\n", q);

    _free(p);
    _free(q);

    printf("Completed without errors.\n");
    return 0;
}
