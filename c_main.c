/**************************************************************************
 *
 *     name  :   c_program
 *
 *	   			 use for test all c languae 
 *    
 *	   data  :   2016/08/09
 *		
 *		
 *	  author :   Simen     simple_do@sina.com
 **************************************************************************/
 
/**************************************************************************
 *                        H E A D E R   F I L E S
 **************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <signal.h>	
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stddef.h>


#include <sys/types.h>		/* some systems still require this */
#include <sys/stat.h>
#include <sys/termios.h>	/* for winsize */




/**************************************************************************
 *                          C O N S T A N T S
 **************************************************************************/


/**************************************************************************
 *                          D A T A   T Y P E S
 **************************************************************************/

#define STACK_TYPE	int 
#define STACK_SIZE	100
#define TRUE 	1
#define FALL	0
 /**************************************************************************
 *              D A T A  D E C L A R A T I O N S
 **************************************************************************/


/**************************************************************************
 *              F U N C T I O N   D E C L A R A T I O N S
 **************************************************************************/
void	err_dump(const char *, ...);		
/* {App misc_source} */
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void	err_exit(int, const char *, ...);
void	err_ret(const char *, ...);
void err_sys(const char *, ...);


/**************************************************************************
 * @ Brief
 * arithmetic for all
 *
 *
 ***************************************************************************/

static array_sum(int *a, int n)
{
	return n == 0? 0 : (array_sum(*a, n-1) + a[n-1]);
}

static assic_to_char(int val)
{
	int qual = val/10;

	if(qual != 0)
	{
		assic_to_char(qual);	
	}

	putchar(val%10 + '0');
}

int BinarySearch(int *a, int n, int k)
{
	int mid, left = 0, right = n - 1;

	while (left <= right)
	{
		mid = (left + right)/2;

		if(k < a[mid])
		{
			right = mid - 1;
		}
		else if (k > a[mid])
		{
			left = mid + 1;
		}
		else 
		 	return TRUE;
	}

	return FALSE;
}

int BinarySearch2(int *a, int left, int right, int k)
{
	int mid;

	while (left <= right)
	{
		mid = (left + right)/2;

		if (k < a[mid])
		{
			right = mid -1;
		}
		else if (k == a[mid])
		{
			return mid;
		}
		else
			left = mid + 1;
	}

	return -1;
}

int RecursionBinarySearch(int *a, int left, int right, int k)
{
	
	if(left <= right)
	{
		int mid = (left + right)/2;

		if(k < a[mid])
		{
			RecursionBinarySearch(*a, left, mid-1, k)
		}
		else if(k == a[mid])
		{
			return mid;
		}
		else 
		{
			RecursionBinarySearch(*a, mid + 1, right, k);
		}
	}
	else
	{
		return -1;	
	}
}
/**************************************************************************
 * @ Brief
 * staic array to stack instance 
 *
 *
 ***************************************************************************/
 
static STACK_TYPE stack[STACK_SIZE];
static int top_stack_element = -1;

int isFullStaic(void)
{
	return top_stack_element == STACK_SIZE;
}

int isEmptyStaic(void)
{
	return top_stack_element == -1;
}

void sPushStaic(STACK_TYPE value)
{
	assert(!isFullStaic());
	top_stack_element += 1;
	stack[top_stack_element] = value;
}

void sPopStaic(void)
{
	assert(!isEmptyStaic());

	top_stack_element -= 1;
}

STACK_TYPE sTopStaic(void)
{
	assert(!isEmptyStaic());

	return stack[top_stack_element];
}
/***************************************************************************
 * @ Brief
 * dynamic array to stack instance 
 *
 *
 ***************************************************************************/
static size_t stack_size;
static STACK_TYPE  *stackDyna;
static STACK_TYPE topElementDyna = -1;

void sCreatStack(size_t size)
{
	assert(stack_size == 0);
	
	stack_size = size;

	stackDyna = (STACK_TYPE *)malloc(sizeof(stack_size));

	assert(stackDyna != NULL);
}

void sDestoryStack(void)
{
	assert(stack_size > 0);
	stack_size = 0;
	free(stackDyna);
	
	stackDyna = NULL;
}

int isFullDyna(void)
{
	assert(stackDyna > 0);

	return  topElementDyna == stack_size -1;
}

int isEmptyDyna(void)
{
	assert(stackDyna > 0);

	return topElementDyna == -1;
}

void sPushDyna(STACK_TYPE value)
{
	assert(!isFullDyna());
	
	topElementDyna += 1;

	stack[topElementDyna] = value;
}

void sPopDyna(void)
{
	assert(!isEmptyDyna());

	topElementDyna -= 1;
}

STACK_TYPE sTopDyna(void)
{
	assert(!isEmptyDyna());

	return stack[topElementDyna];
}

/***************************************************************************
 * @ Brief
 * 
 * a linked stack 
 *
 * 
 ***************************************************************************/
typedef struct STACK_NODE
{
	STACK_TYPE	 		value;	
	struct STACK_NODE 	*next;
	
}StackNode;

static StackNode *stack_link;


int isFullLink(void)
{
	return FALL;
}

int isEmptyLink(void)
{
	return stack_link->next == NULL;
}

void sPushLink(STACK_TYPE date)
{
	StackNode *new_node;
	new_node = (StackNode *)malloc(sizeof(StackNode));

	assert(new_node != NULL);

	new_node->value = date;
	new_node->next = stack_link->next;
	stack_link->next = new_node;
}

void sPopLink(void)
{
	StackNode *first_node;
	
	assert(!isEmptyLink());

	first_node = stack_link->next;

	stack_link->next = first_node->next;

	free(first_node);
}

STACK_TYPE sTopLink(void)
{
	assert(!isEmptyLink());
	return stack_link->value;
}

void sCreatStackLink(void)	
{
	return;
}

void sDestoryStackLink(void)
{
	while(!isEmptyLink())
		sPopLink();
}

/***************************************************************************
 * @ Brief
 * 
 * a static array queue
 *
 * 
 ***************************************************************************/
#define QUEUE_TYPE int

#define QUEUE_SIZE 100
#define ARRAY_QUEUE_SIZE (QUEUE_SIZE + 1)

static size_t front = 1;
static size_t rear  = 0;
static QUEUE_TYPE queue[ARRAY_QUEUE_SIZE];
static size_t queue_cnt = 0;

						//  StaticArra  = SA

int sIsEmptySA(void)
{
	return (rear+1) % ARRAY_QUEUE_SIZE == front;
}

int sIsFullSA(void)
{

	return (rear+2) % ARRAY_QUEUE_SIZE == front;
}

void sInsertQueueSA(QUEUE_TYPE value)
{
	assert(!sIsFullSA());
	
	rear = (rear+1) % ARRAY_QUEUE_SIZE;

	queue[rear] = value;
	
}

void sDeleteQueueSA(void)
{
	assert(!sIsEmptySA());
	
	front = (front+1) %	ARRAY_QUEUE_SIZE;
}

QUEUE_TYPE sFirstQueueSA(void)
{
	assert(!sIsEmptySA());
	
	return queue[front];
}

/***************************************************************************
 * @ Brief
 * 
 * a siagle linked 
 *
 * 
 ***************************************************************************/
typedef struct NODE
{
	char 		*name;
	
	int 		vDate;
	struct NODE *next;

}Node;

static Node *sLinkRoot = NULL;

void sCreatSLink(int n, Node *root)
{
	Node *p, *q;
	
	int i;
	
	for(i = 0; i< n; i++)
	{
		p = (Node *)malloc(sizeof (Node));

		if(p = NULL)
		{
			printf("malloc error");
			return;
		}

		p->vDate = i;
		
		if (root == NULL)
		{
			root = p;
			q = p;
		}
		else
		{
			q->next = p;
			q = p;
		}		
	}
	
	p->next = NULL;

	return;
}

void sDestorySLink(Node *root)
{
	Node *p, *q;

	assert((root != NULL) || (root->next !=NULL));
	
	p = root;

	while(p->next != NULL)
	{
		q = p->next;
		 free(p);
		p = q; 
	}

	root->next = NULL;
}

void sInsertHeadSLink(int value, Node *root)
{
	Node *p, *q;
	
	q = root;

	p = malloc(sizeof(Node));

	p->vDate = value;

	if(q == NULL)
	{
		q = p;
	}
	else
	{
		p->next = q->next;

		q->next = p;
	}
	return;	
}

void sInsertEndSLink(int value, Node *root)
{	
	Node *p, *q;
	
	q = root;

	while(q != NULL)
	{
		q = q ->next;
	}

	p = malloc(sizeof(Node));

	p->vDate = value;
	p->next  = NULL;

	q->next = p;
	
}

void sDeleteSLink(int value, Node *root)
{
	Node *p, *q;

	q = p = root;

	while(q->vDate != value && q != NULL)
	{
		p = q;
		q = q->next;
	}

	p->next = q->next;

	free(q);
}

Node *sRersalLink(Node *root)
{
	assert(root != NULL || root ->next != NULL);

	Node *p;
	Node *q = NULL;

	while(root != NULL)
	{
		p = root->next;

		root->next = q;

		q = root;

		root = p;
	}

	return q;
}

void sPrintfResalLink(Node *pHead)
{

	if(pHead != NULL)
	{
		if(pHead->next != NULL)
		{
			sPrintfResalLink(pHead->next);
		}

		printf("%d \n",pHead->vDate);
	}

	return;
}

char* mystrcpy(char *dst, const char *str)
{
	char *tmp = dst;

	while((*dst++ = *str++) != '\0');

	return tmp;
}


int glob = 6;
char buf[] = "a write to stdout\n";

int main(int argc, char *argv[])
{
	int		var;		/* automatic variable on the stack */	

	pid_t	pid;	
	var = 88;	
	
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)		
			printf("write error");	printf("before fork\n");	

	/* we don't flush stdout */	
	if ((pid = fork()) < 0) 
	{		
		printf("fork error");	
	}
	else if (pid == 0) 
	{		
		/* child */		
		glob++;					
		/* modify variables */		
		var++;	
	} 
	else 
	{		
		sleep(2);				
		/* parent */	
	}	

	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);

	return 0;
}


