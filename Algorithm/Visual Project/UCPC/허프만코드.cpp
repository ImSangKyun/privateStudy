#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
	int weight;	//����ġ
	char ch;	//����
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct {
	TreeNode* ptree;
	char ch;
	int key;	//�󵵼�?
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// ���� �Լ�
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}
// ���� ����� ������ heap_size�� ���� h�� item�� �����Ѵ�.
// ���� �Լ�
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}
// ���� �Լ�
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// ���� Ʈ�� ���� �Լ�
TreeNode* make_tree(TreeNode* left,
	TreeNode* right)
{
	TreeNode* node =
		(TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}
// ���� Ʈ�� ���� �Լ�
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

	// 1�� �����ϰ� ��ȯȣ���Ѵ�.
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}

	// 0�� �����ϰ� ��ȯȣ���Ѵ�.
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	// �ܸ�����̸� �ڵ带 ����Ѵ�.
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

void get_codes(TreeNode* root, int codes[], int top, char * charset, char(*charcode)[100], int n) {
	// 1�� �����ϰ� ��ȯȣ���Ѵ�.
	if (root->left) {
		codes[top] = 1;
		get_codes(root->left, codes, top + 1, charset, charcode, n);
	}

	// 0�� �����ϰ� ��ȯȣ���Ѵ�.
	if (root->right) {
		codes[top] = 0;
		get_codes(root->right, codes, top + 1, charset, charcode, n);
	}

	// �ܸ�����̸� �ڵ带 ����Ѵ�.
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

// ������ �ڵ� ���� �Լ�
void huffman_tree(int freq[], char ch_list[], int n, element *res)	//n:������ ����
{
	int i;
	TreeNode *node, *x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	//�����ͷ� HEAP ����
	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}

	for (i = 1; i < n; i++) {
		// �ּҰ��� ������ �ΰ��� ��带 ����
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// �ΰ��� ��带 ��ģ��.
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		//printf("%d+%d->%d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // ���� Ʈ��
	print_codes(e.ptree, codes, top);
	(*res) = e;
	//destroy_tree(e.ptree);//
	free(heap);
}

char* huffman_encode(char code[], int codeCnt, element * e) {
	//������ Ʈ�� �̿� ��Ʈ�������� ��ȯ, ������ 0 �������� 1. ���� ��忡 �ٴٸ��� ���� ���.
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
		if (j == charset_idx) {	//�������� �������
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

	//charcode�� Code ����
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
	//�־��� ���� �̿�. 0�̸� ���� ���, 1�̸� ������ ����. ���� ��忡�� ���� ��� �� �ٽ� ��Ʈ�� ���ư� ���� ���ڸ� �̿��ؼ� Ž��.

	int length = strlen(code);

	char * res = (char*)malloc(sizeof(char) * 100);
	int res_idx = 0;

	TreeNode * tmp = (*e).ptree;
	for (int i = 0; i < length; ++i) {
		if (code[i] == '1')	//1�ϰ�� ����
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