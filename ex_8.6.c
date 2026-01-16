/*The standard library function calloc(n,size) returns a pointer to n objects of
size size, with the storage initialized to zero. Write calloc, by calling malloc or by
modifying it.*/

#include <stdio.h>
#include <unistd.h>

typedef long Align;      

union header {          
    struct {
        union header *ptr; 
        unsigned size;     
    } s;
    Align x;              
};

typedef union header Header;

static Header base;      
static Header *freep = NULL;  

#define NALLOC 1024       

void _free(void *ap)
{
    Header *bp, *p;

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
    _free((void *)(up + 1));
    return freep;
}

void *_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {   
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
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

void *_calloc(unsigned n, unsigned size)
{
    unsigned total;
    char *p;
    unsigned i;

    total = n * size;
    p = (char *) _malloc(total);

    if (p == NULL)
        return NULL;

    for (i = 0; i < total; i++)
        p[i] = 0;

    return (void *) p;
}

int main(void)
{
    int *arr;
    int i;

    arr = (int *) _calloc(5, sizeof(int));

    if (arr == NULL) {
        printf("calloc failed\n");
        return 1;
    }

    printf("Values after calloc:\n");
    for (i = 0; i < 5; i++)
        printf("arr[%d] = %d\n", i, arr[i]);

    _free(arr);
    return 0;
}
