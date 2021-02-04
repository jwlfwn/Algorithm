#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	struct node *next;
	int elem;
}node;

typedef struct vertex
{
	struct node *outedges;
	struct node *inedges;
	char name;
	int indegree;
}vertex;

typedef struct edge
{
	int origin;
	int destination;
}edge;

typedef struct Graph
{
	vertex *vertices;
	edge *edges;
}Graph;

typedef struct Queue
{
	int front;
	int rear;
	int *queue;
}Queue;

int n, m;
int *topOrder;
Graph G;
Queue Q;

void buildGraph();
void insertVertex(char, int);
void insertDirectedEdge(char, char, int);
int index(char);
void insertFirst(node *, int);
node *getnode(int);
void topologicalSort();
int isEmpty();
void Enqueue(int);
int Dequeue();
void freeAll();

int main()
{
	buildGraph();
	topologicalSort();
	if (topOrder[0] == 0)
		printf("0\n");
	else
	{
		for (int i = 1; i <= n; i++)
			printf("%c ", G.vertices[topOrder[i]].name);
	}
	freeAll();
	return 0;
}

void buildGraph()
{
	char vName, uName, wName;

	scanf("%d", &n); getchar();
	G.vertices = (vertex*)malloc(sizeof(vertex)*n);
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &vName); getchar();
		insertVertex(vName, i);
	}

	scanf("%d", &m); getchar();
	G.edges = (edge*)malloc(sizeof(edge)*m);
	for (int i = 0; i < m; i++)
	{
		scanf("%c %c", &uName, &wName); getchar();
		insertDirectedEdge(uName, wName, i);
	}
	return;
}

void insertVertex(char vName, int i)  // ������ ���� �ְ� ����&���Ⱓ�� �ʱ�ȭ
{
	G.vertices[i].name = vName;
	G.vertices[i].outedges = (node*)malloc(sizeof(node));
	G.vertices[i].outedges->next = NULL;
	G.vertices[i].inedges = (node*)malloc(sizeof(node));
	G.vertices[i].inedges->next = NULL;
	G.vertices[i].indegree = 0;
	return;
}

void insertDirectedEdge(char uName, char wName, int i)  // ���Ⱓ���� ������ ���� �ش��ϴ� �����ε������� �־���
{
	int u, w;
	u = index(uName);
	w = index(wName);
	G.edges[i].origin = u;
	G.edges[i].destination = w;
	insertFirst(G.vertices[u].outedges, i);
	insertFirst(G.vertices[w].inedges, i);
	G.vertices[w].indegree++;  // �������� ����
	return;
}

int index(char vName)
{
	for (int i = 0; i < n; i++)
	{
		if (G.vertices[i].name == vName)
			return i;
	}
}

void insertFirst(node *H, int i)  // ���° ���Ⱓ������(�������ε���) ����&���Ⱓ���� �־���
{
	node *newnode = getnode(i);
	newnode->next = H->next;
	H->next = newnode;
	return;
}

node *getnode(int elem)
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->elem = elem;
	newnode->next = NULL;
	return newnode;
}

void topologicalSort()
{
	int u;
	int *in = (int*)malloc(sizeof(int)*n);  // ���� i�� ��������
	topOrder = (int*)malloc(sizeof(int)*(n + 1));  // 1~n : ������ �������, 0 : �������Ŭ ����
	Q.queue = (int*)malloc(sizeof(int)*n);
	Q.front = -1; Q.rear = -1;

	for (int i = 0; i < n; i++)
	{
		in[i] = G.vertices[i].indegree;  // ���������� in[i]�� �־���
		if (in[i] == 0)  // ���������� 0�� "������ �ε���" �� ť�� �־���
			Enqueue(i);
	}

	int t = 1, e, w;
	node *cur;
	while (!isEmpty())
	{
		u = Dequeue();
		topOrder[t] = u;
		t++;
		cur = G.vertices[u].outedges->next;
		while (cur != NULL)
		{
			e = cur->elem;
			w = G.edges[e].destination;
			in[w]--;
			if (in[w] == 0)
				Enqueue(w);  // ���������� 0�� ������ �ε����� ť�� �־���
			cur = cur->next;
		}
	}

	if (t <= n)
		topOrder[0] = 0;  // �������Ŭ ����
	else
		topOrder[0] = 1;  // G = DAG
	free(in);
	return;
}

int isEmpty()
{
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}

void Enqueue(int i)
{
	Q.rear = (Q.rear + 1) % n;
	Q.queue[Q.rear] = i;
	return;
}

int Dequeue()
{
	Q.front = (Q.front + 1) % n;
	return Q.queue[Q.front];
}

void freeAll()
{
	node *cur, *prev, *cur_, *prev_;
	for (int i = 0; i < n; i++)
	{
		cur = G.vertices[i].outedges->next;
		prev = G.vertices[i].outedges;
		while (cur != NULL)
		{
			free(prev);
			prev = cur;
			cur = cur->next;
		}
		free(prev);
		
		cur_ = G.vertices[i].inedges->next;
		prev_ = G.vertices[i].inedges;
		while (cur_ != NULL)
		{
			free(prev_);
			prev_ = cur_;
			cur_ = cur_->next;
		}
		free(prev_);
	}
	free(G.vertices);
	free(G.edges);
	free(topOrder);
	free(Q.queue);
	return;
}