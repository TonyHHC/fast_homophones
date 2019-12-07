/* make -f mvm_adt.mk */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fmvm.h"

mvm* mvm_init(void)
{
	mvm *p = (mvm*)malloc(sizeof(mvm));

	p->head = NULL;
	p->tail = NULL;
	p->numkeys = 0;

	return p;
}

int mvm_size(mvm* m)
{
	if (m == NULL)
		return 0;

	return m->numkeys;
}

void mvm_insert(mvm* m, char* key, char* data)
{
	mvmcell *old_head;
	mvmcell *np;

	if (m == NULL || key == NULL || data == NULL)
		return;

	np = (mvmcell*)malloc(sizeof(mvmcell));
	np->key = key;
	np->data = data;
	np->next = NULL;
	np->prev = NULL;

	if (m->head == NULL)
	{
		m->head = m->tail = np;
	}
	else
	{
		old_head = m->head;
		m->head = np;
		np->next = old_head;
		old_head->prev = np;
	}

	m->numkeys++;
}

char* mvm_print(mvm* m)
{
	mvmcell *p;

	char *strResult;
	char *strTmp;

	if (m == NULL)
		return NULL;

	strResult = (char*)malloc(10000 * sizeof(char));
	strTmp = (char*)malloc(100 * sizeof(char));
	sprintf(strResult, "");

	p = m->head;

	while (p != NULL)
	{
		if (p->key != NULL && p->data != NULL)
		{
			sprintf(strTmp, "[%s](%s) ", p->key, p->data);
			strcat(strResult, strTmp);
		}
		p = p->next;
	}

	return strResult;
}

void mvm_delete(mvm* m, char* key)
{
	mvmcell *current, *prev;
	prev = NULL;

	if (m == NULL || key == NULL)
		return;

	current = m->head;

	/* if head*/
	if (current != NULL && strcmp(current->key, key) == 0)
	{
		if (m->head == m->tail)
			m->tail = NULL;
		m->head = current->next;
		free(current);
		m->numkeys--;
		return;
	}

	/* if not head */
	while (current != NULL && strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}

	if (current == NULL) return;

	prev->next = current->next;
	prev->next->prev = current->prev;

	if (current == m->tail)
		m->tail = current->prev;

	m->numkeys--;

	free(current);

}

char* mvm_search(mvm* m, char* key)
{
	mvmcell *p, *q;
	p = m->head;
	q = m->tail;

	while (p != NULL && q != NULL)
	{
		if (strcmp(p->key, key) == 0)
			return p->data;
		if (strcmp(q->key, key) == 0)
			return q->data;

		p = p->next;
		if (p == q)
			break;
		q = q->prev;
	}

	return NULL;
}

char** mvm_multisearch(mvm* m, char* key, int* n)
{
	int iCount = 0;
	char **c;
	int iIndex = 0;

	mvmcell *p, *q;
	p = m->head;
	q = m->tail;
	while (p != NULL && q != NULL)
	{
		if (strcmp(p->key, key) == 0)
			iCount++;
		if (strcmp(q->key, key) == 0)
			iCount++;

		p = p->next;
		if (p == q)
			break;
		q = q->prev;
	}

	*n = iCount;

	c = (char**)calloc(iCount, sizeof(char*));
	iIndex = 0;

	p = m->head;
	q = m->tail;
	while (p != NULL && q != NULL)
	{
		if (strcmp(p->key, key) == 0)
		{
			c[iIndex] = p->data;
			iIndex++;
		}
		if (strcmp(q->key, key) == 0)
		{
			c[iIndex] = q->data;
			iIndex++;
		}

		p = p->next;
		if (p == q)
			break;
		q = q->prev;
	}

	return(c);
}

void mvm_free(mvm** p)
{
	mvmcell *current;
	mvmcell *next;

	current = (*p)->head;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	(*p)->numkeys = 0;

	free(*p);
	*p = NULL;
}