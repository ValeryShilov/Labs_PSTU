﻿#include <iostream>
#include <fstream>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

struct Queue
{
	Node* front;
	Node* back;
	int size;
	void init()
	{
		front = nullptr;
		back = nullptr;
		size = 0;
	}
};

void push(Queue*& queue, int data)
{
	Node* tmp = new Node;
	tmp->data = data;
	tmp->next = nullptr;
	if (queue->size == 0)
	{
		queue->front = tmp;
		queue->back = tmp;
	}
	else
	{
		queue->back->next = tmp;
		queue->back = tmp;
	}
	queue->size++;
}

void pop(Queue*& queue)
{
	if (queue->size == 0)
	{
		return;
	}
	queue->front = queue->front->next;
	queue->size--;
}
void insert_element(Queue*& queue, int pos, int data)
{
	Queue* tmp = new Queue;
	tmp->init();
	for (int i = 1; i < pos; i++)
	{
		push(tmp, queue->front->data);
		pop(queue);
	}
	push(tmp, data);
	int init_size = queue->size;
	for (int i = 0; i < init_size; i++)
	{
		push(tmp, queue->front->data);
		pop(queue);
	}
	queue = tmp;
}
void insert_elements(Queue*& queue, int pos, int k)
{
	Queue* tmp = new Queue;
	tmp->init();
	int data;
	cout << "Введите элементы, которые вы хотите вставить: ";
	for (int i = 1; i < pos; i++)
	{
		push(tmp, queue->front->data);
		pop(queue);
	}
	for (int i = 0; i < k; i++)
	{
		cin >> data;
		push(tmp, data);
	}
	int init_size = queue->size;
	for (int i = 0; i < init_size; i++)
	{
		push(tmp, queue->front->data);
		pop(queue);
	}
	queue = tmp;
}
void delete_element(Queue*& queue, int pos)
{
	Queue* tmp = new Queue;
	tmp->init();
	for (int i = 1; i < pos; i++)
	{
		push(tmp, queue->front->data);
		pop(queue);
	}
	pop(queue);
	int init_size = queue->size;
	for (int i = 0; i < init_size; i++)
	{
		push(tmp, queue->front->data);
		pop(queue);
	}
	queue = tmp;
}

void delete_elements(Queue*& queue, int pos, int k)
{
	Queue* tmp = new Queue;
	tmp->init();
	for (int i = 1; i < pos; i++)
	{
		push(tmp, queue->front->data);
		pop(queue);
	}
	for (int i = 0; i < k; i++)
	{
		pop(queue);
	}
	int init_size = queue->size;
	for (int i = 0; i < init_size; i++)
	{
		push(tmp, queue->front->data);
		pop(queue);
	}
	queue = tmp;
}


Queue* createQueue(int n)
{
	Queue* queue = new Queue;
	queue->init();
	int data;
	for (int i = 0; i < n; i++)
	{
		cin >> data;
		push(queue, data);
	}
	return queue;
}

void printQueue(Queue*& queue)
{
	Node* curr = new Node;
	curr = queue->front;
	if (queue->size == 0)
	{
		cout << "Очередь не создана\n";
		return;
	}
	for (int i = 0; i < queue->size; i++)
	{
		cout << curr->data << ' ';
		curr = curr->next;
	}
	cout << endl;
}

void infile(Queue*& queue)
{
	ofstream in; 
	in.open("file.txt");
	Node* curr = new Node;
	curr = queue->front;
	for (int i = 0; i < queue->size; i++)
	{
		in << curr->data << ' ';
		curr = curr->next;
	}
	in.close();
	cout << "Очередь записана в файл" << endl;
}

Queue* recovery(int n)
{
	ifstream out;
	out.open("file.txt");
	Queue* queue = new Queue;
	queue->init();
	int data;
	for (int i = 0; i < n; i++)
	{
		out >> data;
		push(queue, data);
	}
	return queue;
}

void destroy(Queue*& queue)
{
	for (int i = 0; i < queue->size; i++)
	{
		queue->front = queue->front->next;
	}
	queue->size = 0;
	cout << "Очередь уничтожена\n";
}

int main()
{
	system("chcp 1251 > nul");
	int size, data, pos, k, element, size2;
	cout << "Введите размер очереди: ";
	cin >> size;
	cout << "Введите элементы: " << endl;
	Queue* queue = createQueue(size);
	system("cls");
	cout << "Очередь: ";
	printQueue(queue);
	infile(queue);
	cout << "Введите элемент для добавления в конец очереди: ";
	cin >> data;
	push(queue, data);
	cout << "Очередь: ";
	printQueue(queue);
	cout << "Введите количество для вставки: ";
	cin >> k;
	cout << "Введите позицию для вставки: ";
	cin >> pos;
	insert_elements(queue, pos, k);
	cout << "Очередь: ";
	printQueue(queue);
	cout << "Введите количество удаляемых элементов: ";
	cin >> k;
	cout << "Введите позицию с которой удалять элементы: ";
	cin >> pos;
	delete_elements(queue, pos, k);
	cout << "Очередь: ";
	printQueue(queue);
	cout << "Запись очереди в файл" << endl;
	size2 = size;
	infile(queue);
	cout << "Уничтожение очереди" << endl;
	system("pause");
	destroy(queue);
	cout << "Восстановление очереди из файла" << endl;
	queue = recovery(size2);
	printQueue(queue);
	system("pause");
	return 0;
}