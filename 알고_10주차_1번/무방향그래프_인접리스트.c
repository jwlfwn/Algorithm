#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct vertex
{
	struct vertex *next;
	int elem;
}vertex;

typedef struct edge
{
	int endpoints[2];
	int elem;
}edge;

vertex *getnode(int);
int opposite(int, vertex *, edge *);
void print_adjacent_verticesAndweight(int, vertex *, edge *);
void update_edge(int, int, int, vertex *, edge **, int *);
void update_incidence_list(int, int, int, int, vertex *);
void clearAll(vertex *);

void main()
{
	int node_num, a, b, w, edge_len = 8;
	char str;
	vertex *cur = NULL;
	vertex *vertices = (vertex*)malloc(sizeof(vertex) * 6);
	edge *edges = (edge*)malloc(sizeof(edge) * 8);

	for (int i = 0; i < 6; i++)
	{
		(vertices + i)->elem = i + 1;
		(vertices + i)->next = (vertex*)malloc(sizeof(vertex));
		(vertices + i)->next->next = NULL;
	}

	cur = vertices[0].next;
	cur->next = getnode(0); cur = cur->next;
	cur->next = getnode(1); cur = cur->next;
	cur->next = getnode(2); cur = cur->next;
	cur->next = getnode(3);

	cur = vertices[1].next;
	cur->next = getnode(0); cur = cur->next;
	cur->next = getnode(4);

	cur = vertices[2].next;
	cur->next = getnode(1); cur = cur->next;
	cur->next = getnode(4); cur = cur->next;
	cur->next = getnode(5);

	cur = vertices[3].next;
	cur->next = getnode(2);

	cur = vertices[4].next;
	cur->next = getnode(5); cur = cur->next;
	cur->next = getnode(6); cur = cur->next;
	cur->next = getnode(7);

	cur = vertices[5].next;
	cur->next = getnode(3); cur = cur->next;
	cur->next = getnode(7);

	edges[0].endpoints[0] = 0;
	edges[0].endpoints[1] = 1;
	edges[0].elem = 1;
	edges[1].endpoints[0] = 0;
	edges[1].endpoints[1] = 2;
	edges[1].elem = 1;
	edges[2].endpoints[0] = 0;
	edges[2].endpoints[1] = 3;
	edges[2].elem = 1;
	edges[3].endpoints[0] = 0;
	edges[3].endpoints[1] = 5;
	edges[3].elem = 2;
	edges[4].endpoints[0] = 1;
	edges[4].endpoints[1] = 2;
	edges[4].elem = 1;
	edges[5].endpoints[0] = 2;
	edges[5].endpoints[1] = 4;
	edges[5].elem = 4;
	edges[6].endpoints[0] = 4;
	edges[6].endpoints[1] = 4;
	edges[6].elem = 4;
	edges[7].endpoints[0] = 4;
	edges[7].endpoints[1] = 5;
	edges[7].elem = 3;

	while (1)
	{
		scanf("%c", &str);
		switch (str)
		{
		case 'a':
			scanf("%d", &node_num); getchar();
			print_adjacent_verticesAndweight(node_num - 1, vertices, edges);
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &w); getchar();
			if (a <= b)
				update_edge(a - 1, b - 1, w, vertices, &edges, &edge_len);
			else
				update_edge(b - 1, a - 1, w, vertices, &edges, &edge_len);
			break;
		case 'q':
			exit(-1);
			break;
		}
	}

	for (int i = 0; i < 6; i++)
		clearAll((vertices + i)->next);
	free(vertices);
	free(edges);
	return;
}

vertex *getnode(int e)
{
	vertex *newnode = (vertex*)malloc(sizeof(vertex));
	newnode->next = NULL;
	newnode->elem = e;
	return newnode;
}

int opposite(int k, vertex *v, edge *e)
{
	int i = v->elem, u, w;
	u = (e + i)->endpoints[0];
	w = (e + i)->endpoints[1];
	if (k == u)
		return w;
	else
		return u;
}

void print_adjacent_verticesAndweight(int k, vertex *vertices, edge *edges)
{
	int result;
	vertex *cur = (vertices + k)->next;

	if (k < 0 || k > 5)
	{
		printf("-1\n");
		return;
	}

	while (cur->next != NULL)
	{
		result = opposite(k, cur->next, edges);
		printf(" %d %d", (vertices + result)->elem, (edges + cur->next->elem)->elem);
		cur = cur->next;
	}
	printf("\n");
	return;
}

void update_edge(int a, int b, int w, vertex *vertices, edge **pedges, int *edge_len)
{
	int index = 0;
	edge *copy = NULL, *del = NULL;

	if (a < 0 || a > 5 || b < 0 || b > 5)
	{
		printf("-1\n");
		return;
	}

	if (w != 0)
	{
		for (int i = 0; i < *edge_len; i++)
		{
			if ((*pedges + i)->endpoints[0] == a && (*pedges + i)->endpoints[1] == b)
			{
				(*pedges + i)->elem = w;
				return;
			}
		}

		for (int i = 0; i < *edge_len; i++)
		{
			if ((*pedges + i)->endpoints[0] > a)
				break;
			else if ((*pedges + i)->endpoints[0] < a)
				index++;
			else
			{
				if ((*pedges + i)->endpoints[1] > b)
					break;
				else
					index++;
			}
		}

		(*edge_len)++;
		copy = (edge*)malloc(sizeof(edge)*(*edge_len));
		for (int i = 0; i < index; i++)
		{
			(copy + i)->elem = (*pedges + i)->elem;
			(copy + i)->endpoints[0] = (*pedges + i)->endpoints[0];
			(copy + i)->endpoints[1] = (*pedges + i)->endpoints[1];
		}
		(copy + index)->elem = w;
		(copy + index)->endpoints[0] = a;
		(copy + index)->endpoints[1] = b;
		for (int i = index + 1; i < *edge_len; i++)
		{
			(copy + i)->elem = (*pedges + i - 1)->elem;
			(copy + i)->endpoints[0] = (*pedges + i - 1)->endpoints[0];
			(copy + i)->endpoints[1] = (*pedges + i - 1)->endpoints[1];
		}
		del = *pedges;
		*pedges = copy;
		free(del);
		update_incidence_list(index, a, b, w, vertices);
	}
	else
	{
		int flag = 0;
		for (int i = 0; i < *edge_len; i++)
		{
			if ((*pedges + i)->endpoints[0] == a && (*pedges + i)->endpoints[1] == b)
			{
				index = i;
				flag = 1;
				break;
			}
		}
		if (flag == 0)  // a,b사이에 간선이 없는데 w=0인 경우
			return;

		(*edge_len)--;
		copy = (edge*)malloc(sizeof(edge)*(*edge_len));
		for (int i = 0; i < index; i++)
		{
			(copy + i)->elem = (*pedges + i)->elem;
			(copy + i)->endpoints[0] = (*pedges + i)->endpoints[0];
			(copy + i)->endpoints[1] = (*pedges + i)->endpoints[1];
		}
		for (int i = index; i < *edge_len; i++)
		{
			(copy + i)->elem = (*pedges + i + 1)->elem;
			(copy + i)->endpoints[0] = (*pedges + i + 1)->endpoints[0];
			(copy + i)->endpoints[1] = (*pedges + i + 1)->endpoints[1];
		}
		del = *pedges;
		*pedges = copy;
		free(del);
		update_incidence_list(index, a, b, w, vertices);
	}
	return;
}

void update_incidence_list(int index, int a, int b, int w, vertex *vertices)
{
	vertex *cur = NULL, *del = NULL;

	if (w != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			cur = (vertices + i)->next;
			while (cur->next != NULL)
			{
				if (cur->next->elem >= index)
					cur->next->elem++;
				cur = cur->next;
			}
		}

		cur = (vertices + a)->next;
		while (cur->next != NULL && cur->next->elem < index)
			cur = cur->next;
		if (cur->next != NULL && cur->next->elem > index)
		{
			vertex *newnode = getnode(index);
			newnode->next = cur->next;
			cur->next = newnode;
		}
		else
		{
			cur->next = getnode(index);
		}
		if (a != b)
		{
			cur = (vertices + b)->next;
			while (cur->next != NULL && cur->next->elem < index)
				cur = cur->next;
			if (cur->next != NULL && cur->next->elem > index)
			{
				vertex *newnode = getnode(index);
				newnode->next = cur->next;
				cur->next = newnode;
			}
			else
			{
				cur->next = getnode(index);
			}
		}
	}
	else
	{
		int flag = 0;
		for (int i = 0; i < 6; i++)
		{
			cur = (vertices + i)->next;
			while (cur->next != NULL)
			{
				if (cur->next->elem > index)
					cur->next->elem--;
				cur = cur->next;
			}
		}

		cur = (vertices + a)->next;
		while (index != cur->next->elem)  // ★
		{
			cur = cur->next;
			if (cur->next->next == NULL)  // 삭제할 노드가 마지막노드라면 flag = 1
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			del = cur->next;
			cur->next = NULL;
			free(del);
			flag = 0;
		}
		else
		{
			del = cur->next;
			cur->next = del->next;
			del->next = NULL;
			free(del);
		}
		if (a != b)
		{
			cur = (vertices + b)->next;
			while (index != cur->next->elem)
			{
				cur = cur->next;
				if (cur->next->next == NULL)
				{
					flag = 1;
					break;
				}
			}
			if (flag == 1)
			{
				del = cur->next;
				cur->next = NULL;
				free(del);
				flag = 0;
			}
			else
			{
				del = cur->next;
				cur->next = del->next;
				del->next = NULL;
				free(del);
			}
		}
	}
	return;
}

void clearAll(vertex *head)
{
	vertex * temp = head->next;
	while (temp != NULL)
	{
		free(head);
		head = temp;
		temp = temp->next;
	}
	free(head);
	return;
}