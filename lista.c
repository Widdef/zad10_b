#include "lista.h"


void list_add_end(list **p, int value)
{
	list **marker = p;
	list *new_el = (list*)malloc(sizeof(list));
	if(*p == NULL)
		while (*marker)
		{
			marker = &(*marker)->next;
		}
	else
		while ((*marker)->next)
		{
			marker = &(*marker)->next;
		}
	new_el->prev = *marker;
	new_el->data = value;
	new_el->next = *p;
	if (*p == NULL)
		*marker = new_el;
	else
		(*marker)->next = new_el;
}

void list_add_start(list **p, int value)
{
	if (*p == NULL)
	{
		list *new_el = (list*)malloc(sizeof(list));
		new_el->prev = new_el;
		new_el->data = value;
		new_el->next = new_el;
		*p = new_el;
	}
	else
	{
		list *marker = *p;
		list *new_el = (list*)malloc(sizeof(list));
		new_el->data = value;
		new_el->next = *p;
		while ((*p)->next != marker)
		{
			(*p) = (*p)->next;
		}
		new_el->prev = marker;
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
		list *tmp = *p;
		*p = (*p)->next;
		(*p)->prev = NULL;
		free(tmp);
	}
}

void list_delete_last(list **p)
{
	if (*p != NULL)
	{
		list **marker = p;
		while ((*marker)->next->next)
		{
			marker = &(*marker)->next;
		}
		list *tmp = (*marker)->next;
		(*marker)->next = NULL;
		free(tmp);
	}
}


int list_find(list **p, int value)
{
	int flag = 0;
	int index = 0;
	list **marker = p;
	while (*marker != NULL)
	{
		index++;
		if ((*marker)->data == value)
		{
			flag = 1;
			break;
		}
		marker = &(*marker)->next;
	}
	if (flag)
	{
		printf("Element exist. Index: %d\n", index);
		return 1;
	}
	printf("Element not exist\n");
	return 0;
}

void list_find_add_after(list **p, int value, int find)
{
	int flag = 0;
	list **marker = p;
	while (*marker != NULL)
	{
		if ((*marker)->data == find)
		{
			flag = 1;
			break;
		}
		marker = &(*marker)->next;
	}
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
	while (*marker != NULL)
	{
		if ((*marker)->data == find)
		{
			flag = 1;
			break;
		}
		marker = &(*marker)->next;
	}
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
	while ((*marker)->next != NULL)
	{
		index++;
		if ((*marker)->next->data == find)
			break;
		marker = &(*marker)->next;
	}
	if ((*marker)->next != NULL)
	{
		list *tmp = (*marker)->next;
		(*marker)->next = (*marker)->next->next;
		(*marker)->next->next->prev = tmp->prev;
		free(tmp);
	}
	else
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
			while (head != NULL)
			{
				fprintf(fptr,"%d ", head->data);
				head = head->next;
			}
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
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*p = prev;
}
