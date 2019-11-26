#include "lista.h"


void list_add_end(list **p, int value)
{
	list **marker = p;
	list *new_el = (list*)malloc(sizeof(list));
	new_el->data = value;
	if (*p == NULL)
	{
		(*p) = new_el;
		new_el->next = *p;
		new_el->prev = *p;
	}
	else
	{
		while ((*marker)->next != *p)
		{
			marker = &(*marker)->next;
		}
		(*marker)->next = new_el;
		new_el->prev = *marker;
		new_el->next = *p;
		(*p)->prev = new_el;
	}

}

void list_add_start(list **p, int value)
{
	list **marker = p;
	list *new_el = (list*)malloc(sizeof(list));
	new_el->data = value;
	if (*p == NULL)
	{
		(*p) = new_el;
		new_el->next = *p;
		new_el->prev = *p;
	}
	else
	{
		while ((*marker)->next != *p)
		{
			marker = &(*marker)->next;
		}
		(*marker)->next = new_el;
		new_el->prev = *marker;
		new_el->next = *p;
		(*p)->prev = new_el;
		*p = new_el;
	}
}

void list_show(list *p)
{
	printf("\n\n");
	if (p != NULL) 
	{
		list *head = p;
		do
		{
			printf("%d\n", p->data);
			p = p->next;
		}while (p != head);
	}
}
void list_show_from_back(list **p)
{
	list_reverse(p);
	list_show(*p);
	list_reverse(p);
}

void list_delete_first(list **p)
{
	if (*p != NULL)
	{
		list **marker = p;
		list *tmp = *p;
		(*marker)->prev->next = tmp->next;
		(*marker)->next->prev = tmp->prev;
		(*p) = tmp->next;
		free(tmp);
	}
}

void list_delete_last(list **p)
{
	if (*p != NULL)
	{
		list **marker = p;
		list *tmp = (*marker)->prev;
		tmp->prev->next = *p;
		(*p)->prev = tmp->prev;
		free(tmp);
	}
}


int list_find(list **p, int value)
{
	int flag = 0;
	int index = 0;
	list **marker = p;
	if (*p != NULL)
	{
		do
		{
			index++;
			if ((*marker)->data == value)
			{
				flag = 1;
				break;
			}
			marker = &(*marker)->next;
		} while (*marker != *p);
		if (flag)
		{
			printf("Element exist. Index: %d\n", index);
			return 1;
		}
		printf("Element not exist\n");
		return 0;
	}
	else
	{
		printf("Lista pusta\n");
		return 0;
	}
}

void list_find_add_after(list **p, int value, int find)
{
	int flag = 0;
	list **marker = p;
	do
	{
		if ((*marker)->data == find)
		{
			flag = 1;
			break;
		}
		marker = &(*marker)->next;
	}while (*marker != *p);
	if (flag == 1)
	{
		list *new_el = (list*)malloc(sizeof(list));
		new_el->data = value;
		new_el->next = (*marker)->next;
		new_el->prev = *marker;
		(*marker)->next = new_el;
	}
	else
	{
		char dec;
		printf("Element not exist\n");
		do
		{
			printf("Do you want to create element as last element of the list? (Y/N)");
			scanf("%c", &dec);
		} while (dec != 'y' && dec != 'Y' && dec != 'n' && dec != 'N');
		if (dec == 'Y' || dec == 'y')
			list_add_end(p, value);
	}
}

void list_find_add_before(list **p, int value, int find)
{
	int flag = 0;
	list **marker = p;
	do
	{
		if ((*marker)->data == find)
		{
			flag = 1;
			break;
		}
		marker = &(*marker)->next;
	} while (*marker != *p);
	if (flag == 1)
	{
		list *new_el = (list*)malloc(sizeof(list));
		new_el->data = value;
		new_el->next = *marker;
		new_el->prev = (*marker)->prev;
		(*marker)->prev->next = new_el;
	}
	else
	{
		char dec;
		printf("Element not exist\n");
		do
		{
			printf("Do you want to create element as first element of the list? (Y/N)\n");
			scanf("%c", &dec);
		} while (dec != 'y' && dec != 'Y' && dec != 'n' && dec != 'N');
		if (dec == 'Y' || dec == 'y')
			list_add_start(p, value);
	}
}

void list_find_delete(list **p, int find)
{
	int index = 0;
	list **marker = p;
	if ((*marker)->data == find)
	{
		list_delete_first(p);
		return;
	}
	while ((*marker)->next != *p)
	{
		index++;
		if ((*marker)->next->data == find)
			break;
		marker = &(*marker)->next;
	}
	if ((*marker)->next != *p)
	{
		list *tmp = (*marker)->next;
		(*marker)->next = (*marker)->next->next;
		(*marker)->next->next->prev = tmp->prev;
		free(tmp);
	}
	else
		if(list_find(p, find))
			list_delete_last(p);
}

int check_sting(char *str)
{
	int len = (int)strlen(str);
	if ((str[len - 3] == 't') && (str[len - 4] == '.') && (str[len - 2] == 'x') && (str[len - 1] == 't'))
		return 1;
	return 0;
}

void list_from_file(list **head)
{
	int value = 0;
	char file[256];
	FILE *fptr;
	do {
		printf_s("Podaj nazwe pliku: ");
		scanf("%s", &file);
		value = check_sting(file); //Sprawdza czy plik zostal podany z rozszerzeniem txt TAK - 1 NIE - 0 
		if (value)
		{
			fptr = fopen(file, "r");
			if (fptr == NULL) // Czy uda³o siê otworzyæ plik
			{
				printf("Blad otwarcia pliku.\n");
				system("PAUSE");
				fclose(fptr);
				break;
			}
			while (fscanf(fptr, "%d", &value) != EOF)
			{
				list_add_end(head, value);
			}
			printf("Udalo sie odczytac dane z pliku.\n");
			fclose(fptr);
			system("PAUSE");
			break;
		}
		printf("Podales zly format pliku.\n");
		system("PAUSE");
	} while (!value); // Pêtla nie zakonczy sie do momentu podania pliku z rozszerzeniem txt
}

void list_to_file(list *head)
{
	int value;
	char file[256];
	FILE *fptr;
	list *tmp = head;
	do {
		printf_s("Podaj nazwe pliku: ");
		scanf("%s", &file);
		value = check_sting(file); //Sprawdza czy plik zostal podany z rozszerzeniem txt TAK - 1 NIE - 0 
		if (value)
		{
			fptr = fopen(file, "w");
			if (fptr == NULL) // Czy uda³o siê otworzyæ plik
			{
				printf("Blad otwarcia pliku.\n");
				system("PAUSE");
				fclose(fptr);
				break;
			}
			do
			{
				fprintf(fptr,"%d ", head->data);
				head = head->next;
			} while (head != tmp);
			printf("Udalo sie zapisac dane do pliku.\n");
			fclose(fptr);
			system("PAUSE");
			break;
		}
		printf("Podales zly format pliku.\n");
		system("PAUSE");
	} while (!value); // Pêtla nie zakonczy sie do momentu podania pliku z rozszerzeniem txt
}

void list_reverse(list **p) 
{
	list *prev = NULL;
	list *cur = *p;
	list *next;
	if (*p == NULL || (*p)->next == NULL)
		return;
	do
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	} while (cur != *p);
	*p = prev;
}
