#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void swap(char *str1,char*str2)
{
	char *temp=NULL;
	temp=str1;
	str1=str2;
	str2=temp;
	printf("str2= %s\n",str2);
	//strcpy(*str2,*temp);
}
typedef struct List {
	int data;
	struct List *next;
}list_t;

int list_insert(list_t **head,int data,int at)
{
	list_t *new_node=NULL;
	list_t *temp=*head;
	new_node=(list_t*)malloc(sizeof(list_t));
	if(new_node==NULL)
		return -1;
	new_node->data=data;
	if(at <=1)// node is stacked
	{
		new_node->next=*head;
		*head=new_node;
	}
	else
	{
		int i;
		for (i = 2; i < at; i++) {
			if(temp->next ==NULL)
				break;
			temp=temp->next;
		}
		new_node->next=temp->next;
		temp->next=new_node;
		return 0;

	}
	return 0;
}
void list_view(list_t **head)
{
	list_t *temp=*head;
	if(temp==NULL)
		return ;
	int i=1;
	do
	{
		printf("%d. 0x%x\t%d\n",i++,temp,temp->data);
		temp=temp->next;
	}
	while(temp!=NULL);
	printf("\n");
}

int list_remove(list_t **head,list_t **node,int at)
{
	list_t **temp=head;
	if(*head!=NULL)
	{
		if(node!=NULL)
		{
			while(*temp!=*node)
			{
				temp=&((*temp)->next);
			}
			*temp=(*temp)->next;
		}
		else if(at >= 1)
		{
			int i;
			for(i=1;i<at;i++)
			{
				if((*temp)->next ==NULL)
					break;
				temp=&((*temp)->next);
			}
			if(i==at)
				*temp=(*temp)->next;
		}
	}
	return 0;
}
list_t *list_get_node(list_t **head,int at)
{
	list_t **temp=head;
	if(head!=NULL && at >0)
	{
		int i=0;
		for (i = 1; i < at; i++) {
			if((*temp)==NULL)
				return NULL;
			temp=&((*temp)->next);
		}
		if(i ==at)
			return *temp;
	}
	return NULL;
}
int main(int argc, char const *argv[])
{
	list_t *my_list=NULL;
	int i=0;
	for (i = 1; i < 5;i++) {
		list_insert(&my_list,i+3,0);
	}
	list_view(&my_list);
	list_insert(&my_list,10,8);
	list_view(&my_list);
	list_remove(&my_list,NULL,1);
	list_view(&my_list);
	list_t *node1= list_get_node(&my_list,3);
	//printf("Node data: 0x%x %d\n",node1,node1->data);
	list_remove(&my_list,&node1,0);
	list_view(&my_list);
	return 0;
}

