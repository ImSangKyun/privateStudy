#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
	int weight;	//가중치
	char ch;	//문자
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct {
	TreeNode* ptree;
	char ch;
	int key;	//빈도수?
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}
// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.
// 삽입 함수
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}
// 삭제 함수
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left,
	TreeNode* right)
{
	TreeNode* node =
		(TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}
// 이진 트리 제거 함수
void destroy_tree(TreeNode* root)
{
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}
void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top)
{

	// 1을 저장하고 순환호출한다.
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}

	// 0을 저장하고 순환호출한다.
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	// 단말노드이면 코드를 출력한다.
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

void get_codes(TreeNode* root, int codes[], int top, char * charset, char(*charcode)[100], int n) {
	// 1을 저장하고 순환호출한다.
	if (root->left) {
		codes[top] = 1;
		get_codes(root->left, codes, top + 1, charset, charcode, n);
	}

	// 0을 저장하고 순환호출한다.
	if (root->right) {
		codes[top] = 0;
		get_codes(root->right, codes, top + 1, charset, charcode, n);
	}

	// 단말노드이면 코드를 출력한다.
	if (is_leaf(root)) {
		//printf("%c: ", root->ch);
		//print_array(codes, top);

		int i;
		for (i = 0; i < n; ++i) {
			if (charset[i] == root->ch) {
				for (int j = 0; j < top; ++j)
					charcode[i][j] = codes[j] + '0';
			}
		}
	}
}

// 허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n, element *res)	//n:문자의 개수
{
	int i;
	TreeNode *node, *x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	//데이터로 HEAP 생성
	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}

	for (i = 1; i < n; i++) {
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// 두개의 노드를 합친다.
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		//printf("%d+%d->%d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // 최종 트리
	print_codes(e.ptree, codes, top);
	(*res) = e;
	//destroy_tree(e.ptree);//
	free(heap);
}

char* huffman_encode(char code[], int codeCnt, element * e) {
	//허프만 트리 이용 루트에서부터 순환, 왼쪽은 0 오른쪽은 1. 말단 노드에 다다르면 숫자 출력.
	//int * freq; 
	//int * ch_list;

	int charset_idx = 0;
	char charset[100];
	char charcode[100][100];	memset(charcode, 0, sizeof(charcode));
	int freq[100];	memset(freq, 0, sizeof(freq));

	//Freq, charset
	for (int i = 0; i < codeCnt; ++i) {
		//TODO
		int j;
		for (j = 0; j < charset_idx; ++j) {
			if (charset[j] == code[i]) {
				freq[j]++;
				break;
			}
		}
		if (j == charset_idx) {	//같은값이 없을경우
			charset[charset_idx++] = code[i];
			freq[j] = 1;
		}
	}

	//char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	huffman_tree(freq, charset, charset_idx, e);


	//print encoding
	int codes[100];
	int top = 0;
	//print_codes((*e).ptree, codes, top);

	//charcode에 Code 생성
	get_codes((*e).ptree, codes, top, charset, charcode, charset_idx);

	char * res = (char*)malloc(sizeof(char) * 256);
	memset(res, 0, sizeof(res));

	for (int i = 0; i < codeCnt; ++i) {
		for (int j = 0; j < charset_idx; ++j) {
			if (code[i] == charset[j]) {
				strcat(res, charcode[j]);
			}
		}
	}
	return res;
}

char * huffman_decode(char * code, element * e) {
	//주어진 숫자 이용. 0이면 왼쪽 노드, 1이면 오른쪽 노드로. 말단 노드에서 문자 출력 후 다시 루트로 돌아가 남은 숫자를 이용해서 탐색.

	int length = strlen(code);

	char * res = (char*)malloc(sizeof(char) * 100);
	int res_idx = 0;

	TreeNode * tmp = (*e).ptree;
	for (int i = 0; i < length; ++i) {
		if (code[i] == '1')	//1일경우 왼쪽
			tmp = tmp->left;
		else
			tmp = tmp->right;

		if (is_leaf(tmp)) {
			res[res_idx++] = tmp->ch;
			tmp = (*e).ptree;
		}
	}
	res[res_idx] = '\0';

	return res;
}

int main(void)
{

	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4, 6, 8, 12, 15 };
	//huffman_tree(freq, ch_list, 5);
	char *s;
	char *t;
	//s = malloc(sizeof(char));
	//t = malloc(sizeof(char));

	element e;
	s = huffman_encode((char*)"teniis", 6, &e);
	printf("%s\n", s);


	t = huffman_decode(s, &e);
	printf("%s\n", t);

	return 0;
}