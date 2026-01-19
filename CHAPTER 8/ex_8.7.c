/*malloc accepts a size request without checking its plausibility; free believes
that the block it is asked to free contains a valid size field. Improve these routines so they
make more pains with error checking.*/

#include <stdio.h>
#include <unistd.h>

#define MAXBYT 10240
#define NALLOC 1024

typedef long Align;

/* block header */
union header {
    struct {
        union header *ptr;  /* next block */
        unsigned size;      /* size in Header units */
    } s;
    Align x;               /* force alignment */
};

typedef union header Header;

static Header base;        
static Header *freep = NULL;
static unsigned maxalloc = 0;

static Header *morecore(unsigned);

void _free(void *ap)
{
    Header *bp, *p;

    if (ap == NULL)
        return;

    bp = (Header *) ap - 1;

    if (bp->s.size == 0 || bp->s.size > maxalloc) {
        fprintf(stderr, "free: invalid block size\n");
        return;
    }

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

void *_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    if (nbytes == 0 || nbytes > MAXBYT) {
        fprintf(stderr, "malloc: invalid size request\n");
        return NULL;
    }

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL)
    {
        base.s.ptr = &base;
        base.s.size = 0;
        freep = &base;
        prevp = freep;  
    }


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

        if (p == freep) {
            if ((p = morecore(nunits)) == NULL)
                return NULL;
        }
    }
}

static Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)
        return NULL;

    up = (Header *) cp;
    up->s.size = nu;

    if (nu > maxalloc)
        maxalloc = nu;

    _free((void *)(up + 1));
    return freep;
}

int main(void)
{
    int *p = _malloc(10 * sizeof(int));
    if (!p) {
        printf("Allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; i++)
        p[i] = i * 10;

    for (int i = 0; i < 10; i++)
        printf("%d ", p[i]);
    printf("\n");

    _free(p);

    _malloc(0);    // invalid size
    _malloc(50000);  // too large

    return 0;
}
