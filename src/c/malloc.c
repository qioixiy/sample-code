// url: http://blog.csdn.net/liujia2100/article/details/30568387
#define UNUSED 0
#define USED 1
#define HEAP_NOTFIND 0
#define HEAP_FOUND  1

static unsigned long HEAP_START = 0x54000000;
static unsigned long HEAP_END = 0x58000000;

typedef struct heap
{
    int size;
    int start;
    int end;
    int used;
    struct heap *next;
    struct heap *prv;
}heap;

static heap *heap_head;
static heap *heap_crrunt;
static heap *heap_mark;
static int heapnum=0;


//初始化堆
void init_heap()
{

    heap_head = (heap *)HEAP_START;
    heap_head->size = (HEAP_END-HEAP_START)-sizeof(heap);
    heap_head->start = HEAP_START+sizeof(heap);
    heap_head->end = HEAP_END;
    heap_head->used = UNUSED;
    heap_head->next = NULL;
    heap_head->prv = NULL;
    heap_crrunt = heap_head;
    heapnum=0;

    printf("HEAP_START=%08x\n",HEAP_START);
    printf("HEAP_END=%08x\n",HEAP_END);


    printf("heap_head=0x%08x\n",heap_crrunt);
    printf("heap_head->start=%08x\n",heap_head->start);
    printf("heap_head->size=0x%08x\n",heap_head->size);



}

//分配内存函数

void * xmalloc(unsigned int size)
{

    heap *newblock;
    heap *prtblock;
    int stat=HEAP_NOTFIND;
    int num = 0;
    size = (size+7)&~7;
//	printf("xmalloc:%d\n",heapnum);

    heap_mark=heap_crrunt;
//	printf("heap_crrunt:0x%08x\n",heap_crrunt);
    while(heap_crrunt->next != heap_mark)
    {
        if(heap_crrunt == NULL)
            heap_crrunt = heap_head;

        if(heap_crrunt->used == UNUSED)
        {
            if(heap_crrunt->size > size)
            {
                newblock = (heap*)((unsigned char *)heap_crrunt+(size+sizeof(heap)));
                newblock->size = heap_crrunt->size-(size+sizeof(heap));
                newblock->start = heap_crrunt->start+(size+sizeof(heap));
                newblock->end = heap_crrunt->end;
                newblock->used = UNUSED;
                newblock->next = heap_crrunt->next;
                newblock->prv = heap_crrunt;
                heap_crrunt->used = USED;
                heap_crrunt->size = size;
                heap_crrunt->end = heap_crrunt->start+size;
                heap_crrunt->next = newblock;
                stat = HEAP_FOUND;
                heapnum++;

                printf("heapnum:%d,heap:0x%08x,heapsize:%d\n",heapnum,heap_crrunt->start,size);

                break;
            }

        }
        num++;
        delay(1);
        if(num > 1000)
        {
            printf("alloc error\n");
            return NULL;
        }
        heap_crrunt = heap_crrunt->next;

    }

    if(stat == HEAP_NOTFIND)
    {
        printf("malloc fail\n");
        return NULL;
    }

    prtblock = heap_crrunt;

    heap_crrunt = newblock;
//	printf("newblock=0x%08x\n",newblock);
//	printf("newblock start=0x%08x\n",newblock->start);

    return ((heap *)((u32)prtblock + sizeof(heap)));
}

//释放
void xfree(void *block)

{
    heap * ptrblock;
    heap * prvblock;
    heap * nextblock;

    if(block==NULL)
        return ;

    ptrblock = (heap *)((unsigned char *)block-sizeof(heap));
    ptrblock->used = UNUSED;
    prvblock = ptrblock->prv;
    nextblock = ptrblock->next;
    printf("xfree\n");
    if(prvblock != NULL)
    {
        if(prvblock->used==UNUSED)
        {
            prvblock->size = prvblock->size+ptrblock->size+sizeof(heap);
            prvblock->end = ptrblock->end;
            prvblock->next = ptrblock->next;
            ptrblock = prvblock;
            heapnum--;
        }
    }
    if(nextblock != NULL)
    {
        if(nextblock->used == UNUSED)
        {
            ptrblock->size = ptrblock->size+nextblock->size+sizeof(heap);
            ptrblock->end = nextblock->end;
            ptrblock->next = ptrblock->next;
            heapnum--;
        }
    }

    heap_crrunt = ptrblock;
}
