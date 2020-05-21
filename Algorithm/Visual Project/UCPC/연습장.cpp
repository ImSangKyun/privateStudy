#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 200
typedef struct {
	char aminoL;
	char aminoR;
} element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int  front, rear;
} DequeType;

typedef char elements;
typedef struct ListNode {
	elements data;
	struct ListNode *link;
} ListNode;

void error(const char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_deque(DequeType *q)
{
	q->front = q->rear = 0;
}

int is_empty(DequeType *q)
{
	return (q->front == q->rear);
}

int is_full(DequeType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void deque_print(DequeType *q)
{
	printf("DEQUE(front=%d rear=%d) :\n ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%c-%c \n ", q->data[i].aminoL, q->data[i].aminoR);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void add_rear(DequeType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element delete_front(DequeType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element get_front(DequeType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType *q, char c)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	element val;
	val.aminoL = c;
	if (c == 'A') { val.aminoR = 'T'; }
	else if (c == 'T') { val.aminoR = 'A'; }
	else if (c == 'G') { val.aminoR = 'C'; }
	else if (c == 'C') { val.aminoR = 'G'; }
	else error("잘못된 입력입니다");


	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType *q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_rear(DequeType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}

ListNode* transcribe(DequeType *q, char side)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	ListNode* tmp = p;
	if (side == 'L') {
		if (!is_empty(q)) {
			int i;
			for (i = q->rear; i != q->front; i = ((i-1) > 0)? i-1: MAX_QUEUE_SIZE -1) {
				if (q->data[i].aminoL == 'T')
					tmp->data = 'U';
				else
					tmp->data = q->data[i].aminoL;
				
				if (i == q->front+1) {
					tmp->link = NULL;
				}
				else {
					tmp->link = (ListNode*)malloc(sizeof(ListNode));
					tmp = tmp->link;
				}
			}
		}
	}
	else if (side == 'R') {
		if (!is_empty(q)) {
			int i;
			for (i = q->rear; i != q->front; i = ((i - 1) > 0) ? i - 1 : MAX_QUEUE_SIZE - 1) {
				if (q->data[i].aminoR == 'T')
					tmp->data = 'U';
				else
					tmp->data = q->data[i].aminoR;

				if (i == q->front + 1) {
					tmp->link = NULL;
				}
				else {
					tmp->link = (ListNode*)malloc(sizeof(ListNode));
					tmp = tmp->link;
				}
			}
		}
	}
	return p;
}

enum Sigma {
	Val, Ala, Asp, Glu, Gly, Phe, Leu, Ser, Tyr, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asna, Lys, Stop
};

enum Sigma resolution(char arr[3]) {
	enum Sigma s;
	switch (arr[0]) {
	case 'G':
		switch (arr[1]) {
		case 'G':
			s = Gly;
			break;
		case 'U':
			s = Val;
			break;
		case 'C':
			s = Ala;
			break;
		case 'A':
			switch (arr[2]) {
			case 'G':
				s = Glu;
				break;
			case 'U':
				s = Asp;
				break;
			case 'C':
				s = Asp;
				break;
			case 'A':
				s = Glu;
				break;
			}
			break;
		}
		break;
	case 'U':
		switch (arr[1]) {
		case 'G':
			switch (arr[2]) {
			case 'G':
				s = Trp;
				break;
			case 'U':
				s = Cys;
				break;
			case 'C':
				s = Cys;
				break;
			case 'A':
				s = Stop;
				break;
			}
			break;
		case 'U':
			switch (arr[2]) {
			case 'G':
				s = Leu;
				break;
			case 'U':
				s = Phe;
				break;
			case 'C':
				s = Phe;
				break;
			case 'A':
				s = Leu;
				break;
			}
			break;
		case 'C':
			s = Ser;
			break;
		case 'A':
			switch (arr[2]) {
			case 'G':
				s = Stop;
				break;
			case 'U':
				s = Tyr;
				break;
			case 'C':
				s = Tyr;
				break;
			case 'A':
				s = Stop;
				break;
			}
			break;
		}
		break;
	case 'C':
		switch (arr[1]) {
		case 'G':
			s = Arg;
			break;
		case 'U':
			s = Leu;
			break;
		case 'C':
			s = Pro;
			break;
		case 'A':
			switch (arr[2]) {
			case 'G':
				s = Gin;
				break;
			case 'U':
				s = His;
				break;
			case 'C':
				s = His;
				break;
			case 'A':
				s = Gin;
				break;
			}
			break;
		}
		break;
	case 'A':
		switch (arr[1]) {
		case 'G':
			switch (arr[2]) {
			case 'G':
				s = Arg;
				break;
			case 'U':
				s = Ser;
				break;
			case 'C':
				s = Ser;
				break;
			case 'A':
				s = Arg;
				break;
			}
			break;
		case 'U':
			switch (arr[2]) {
			case 'G':
				s = Met;
				break;
			case 'U':
				s = Ile;
				break;
			case 'C':
				s = Ile;
				break;
			case 'A':
				s = Ile;
				break;
			}
			break;
		case 'C':
			s = Thr;
			break;
		case 'A':
			switch (arr[2]) {
			case 'G':
				s = Lys;
				break;
			case 'U':
				s = Asna;
				break;
			case 'C':
				s = Asna;
				break;
			case 'A':
				s = Lys;
				break;
			}
			break;
		}
		break;
	}

	return s;
}

void translate(ListNode *head)
{
	enum Sigma s;
	char arr[3];
	int cnt = 0;
	bool flag = true;

	for (ListNode *p = head; p != NULL && flag; p = p->link, ++cnt) {
		if (cnt == 3) {
			s = resolution(arr);
			switch (s) {	//Val, Ala, Asp, Glu, Gly, Phe, Leu, Ser, Tyr, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asna, Lys, Stop
			case Val: printf("Val-"); break;
			case  Ala: printf("Ala-"); break;
			case  Asp: printf("Asp-"); break;
			case  Glu: printf("Glu-"); break;
			case  Gly: printf("Gly-"); break;
			case  Phe: printf("Phe-"); break;
			case  Leu: printf("Leu-"); break;
			case  Ser: printf("Ser-"); break;
			case  Tyr: printf("Tyr-"); break;
			case  Cys: printf("Cys-"); break;
			case  Trp: printf("Trp-"); break;
			case  Pro: printf("Pro-"); break;
			case  His: printf("His-"); break;
			case  Gin: printf("Gin-"); break;
			case  Arg: printf("Arg-"); break;
			case  Ile: printf("Ile-"); break;
			case  Met: printf("Met-"); break;
			case  Thr: printf("Thr-"); break;
			case  Asna: printf("Asna-"); break;
			case  Lys: printf("Lys-"); break;
			case  Stop: 
				error("Stop!");
				flag = false;
				break;
			}
			cnt = 0;
		}
		arr[cnt] = p->data;
	}
	if (cnt == 3) {
		s = resolution(arr);
		switch (s) {	//Val, Ala, Asp, Glu, Gly, Phe, Leu, Ser, Tyr, Cys, Trp, Pro, His, Gin, Arg, Ile, Met, Thr, Asna, Lys, Stop
		case Val: printf("Val"); break;
		case  Ala: printf("Ala"); break;
		case  Asp: printf("Asp"); break;
		case  Glu: printf("Glu"); break;
		case  Gly: printf("Gly"); break;
		case  Phe: printf("Phe"); break;
		case  Leu: printf("Leu"); break;
		case  Ser: printf("Ser"); break;
		case  Tyr: printf("Tyr"); break;
		case  Cys: printf("Cys"); break;
		case  Trp: printf("Trp"); break;
		case  Pro: printf("Pro"); break;
		case  His: printf("His"); break;
		case  Gin: printf("Gin"); break;
		case  Arg: printf("Arg"); break;
		case  Ile: printf("Ile"); break;
		case  Met: printf("Met"); break;
		case  Thr: printf("Thr"); break;
		case  Asna: printf("Asna"); break;
		case  Lys: printf("Lys"); break;
		case  Stop:
			error("Stop!");
			flag = false;
			break;
		}
		cnt = 0;
	}
	else {
		error("3>!");
	}


}

void print_list(ListNode *head)
{
	for (ListNode *p = head; p != NULL; p = p->link) {
		printf("%c->", p->data);
	}
	printf("NULL \n");
}


int main(void)
{
	DequeType queue;

	init_deque(&queue);

	char dna[100];
	printf("Please input DNA sequence: ");
	scanf("%s", dna);
	fflush(stdin);
	//gets(dna);
	int len = strlen(dna);

	for (int i = 0; i < len; i++) {

		add_front(&queue, dna[i]);


	}

	deque_print(&queue);

	//RNA Transcribe start

	ListNode *rna = NULL;

	rna = transcribe(&queue, 'L');

	print_list(rna);


	//RNA Translate start

	translate(rna);

	return 0;
}
