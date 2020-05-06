#include <stdio.h>
#include <stdlib.h>
#define max 200

typedef struct node {

	char harf;
	int freq;
	struct node* left, * right, * next;

}NODE;

void yazdirNode(NODE* head);
int harfiAra(NODE* head, char harf, int* nodeCounter);
void nodeOlustur(NODE* head, char harf);
NODE* insertionSort(NODE* head, int* nodeCounter);
NODE* swapNodes(NODE** nodelar, int j, int* nodeCounter);
NODE* huffman(NODE* head);
NODE* createParrent(NODE* current);
void printGivenLevel(struct node* root, int level);
void printLevelOrder(struct node* root, int nodeCounter);






int main() {

	NODE* head = (NODE*)malloc(sizeof(NODE));

	char yazi[max], temp;
	int i = 0,nodeCounter = 1;
	int* nodeCounterPtr;
	nodeCounterPtr = &nodeCounter;
	

	printf("Metni giriniz : ");
	scanf("%[^\n]s", yazi);
	printf("\n\n");

	if (yazi[i] != NULL) {
		head->harf = yazi[i];
		head->freq = 1;
		head->next = NULL;
		head->left = NULL;
		head->right = NULL;
		i++;

	}

	while (yazi[i] != NULL) {
		harfiAra(head, yazi[i], nodeCounterPtr);
		i++;
	}
	//
	printf("Siralanmamis halde Linked List : \n");
	yazdirNode(head);

	printf("\nNode sayisi : %d \n", nodeCounter);
	printf("\nSiralanmis halde Linked List : \n");
    head = insertionSort(head, nodeCounterPtr);
	yazdirNode(head);

	printf("\n\nHuffman algoritmasinin ileryelisi : \n");
	head = huffman(head);
	printf("\n");

	printf("\n\nAgacin yazdirilmasi : \n");
	printLevelOrder(head,nodeCounter);

	

	return 0;
}

int harfiAra(NODE* head, char harf, int* nodeCounter) {
	NODE* current = head;
	
	while ((current != NULL) && (current->harf != harf)) {
		
		current = current->next;
	}
	if (current == NULL) {
		
		(*nodeCounter)++;
		nodeOlustur(head, harf);
		return 0; // harf mevcut deðil
	}
	else {
		current->freq++;
		return 1;
	}

}

void nodeOlustur(NODE* head, char harf) {

	NODE* current = head;
	NODE* yeniNode = (NODE*)malloc(sizeof(NODE));

	while (current->next != NULL) {
		current = current->next;
	}

	yeniNode->next = NULL;
	yeniNode->harf = harf;
	yeniNode->freq = 1;
	yeniNode->right = NULL;
	yeniNode->left = NULL;
	current->next = yeniNode;

}

void yazdirNode(NODE* head) {
	NODE* current = head;

	while (current != NULL) {
		printf("%c - %d | ", current->harf, current->freq);
		current = current->next;
	}


}

NODE* insertionSort(NODE* head, int* nodeCounter) {

	NODE* current = head;
	NODE** nodelar = (NODE**)malloc((*nodeCounter) * sizeof(NODE*));
	int i = 0,j;

	while (current != NULL) {
		nodelar[i] = current;
		current = current->next;
		i++;
	}
	(*nodeCounter) = i;

	for (i = 1; i < (*nodeCounter); i++) {
		j = i;
		while (j>0 && (nodelar[j]->freq < nodelar[j - 1]->freq)) {

			if (j == 1) {
				head = swapNodes(nodelar, j, nodeCounter);
			}
			else {
				swapNodes(nodelar, j, nodeCounter);
			}
			NODE* tmp = nodelar[j];
			nodelar[j] = nodelar[j - 1];
			nodelar[j - 1] = tmp;
			j--;
		
		}
	}
	return head;
	free(nodelar);
}

NODE* swapNodes(NODE** nodelar, int j ,int* nodeCounter) {

	if (j == (*nodeCounter) - 1 && j != 1) {
		
		nodelar[j - 2]->next = nodelar[j];
		nodelar[j]->next = nodelar[j - 1];
		nodelar[j - 1]->next = NULL;
	}
	else if (j == 1) {
		
		nodelar[j]->next = nodelar[j - 1];
		nodelar[j - 1]->next = nodelar[j + 1];
		return nodelar[j];
	}
	else {
		
		nodelar[j - 2]->next = nodelar[j];
		nodelar[j]->next = nodelar[j - 1];
		nodelar[j - 1]->next = nodelar[j + 1];
	}
	
	return NULL;
}

NODE* huffman(NODE* head) {
	
	NODE* current = head;
	int count = 1;
	while (current->next != NULL) {
		printf("Adim %d : ", count);
		current = createParrent(current);
		yazdirNode(current);
		printf("\n");
		count++;
	}
	return current;

}

NODE* createParrent(NODE* head_ref) {
	
	NODE* yeniNode = (NODE*)malloc(sizeof(NODE));
	NODE* current = head_ref;
	NODE* tmp = head_ref;
	
	
	yeniNode->freq = (head_ref->freq) + (head_ref->next->freq);
	yeniNode->left = head_ref;
	yeniNode->right = head_ref->next;
	yeniNode->harf = ' ';



	if (head_ref->freq >= yeniNode->freq)
	{
		yeniNode->next = head_ref;
		return yeniNode;
	}
	else
	{
		
		while (current->next != NULL &&
			(current->next->freq) < (yeniNode->freq))
		{
			current = current->next;
		}
		yeniNode->next = current->next;
		current->next = yeniNode;
	}
	current = tmp->next->next;
	tmp->next->next = NULL;
	tmp->next = NULL;

	return current;

}

void printLevelOrder(struct node* root, int height)
{
	int h = height-1;
	int i,j;
	for (i = 1; i <= h; i++)
	{
		/*
		for (j = i; j < h; j++) {
			printf("   ");
		}
		*/
		printGivenLevel(root, i);
		printf("\n");
	}
}

void printGivenLevel(struct node* root, int level)
{
	if (root == NULL) {
		printf(" ");
		return;
	}
	if (level == 1)
		printf(" %d%c ", root->freq,root->harf);
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}


