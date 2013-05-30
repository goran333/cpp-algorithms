/*!
 * \file     main.c
 * \brief    Test out reversal of singly linked list
 * \author   Pawan Lakshmanan
 * \date     May 29, 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//define a singly linked list node
typedef struct ll_node_x_
{
  char data;
  struct ll_node_x_ *next;
}ll_node_x;

//local fn prototypes
static ll_node_x *create_list(char last_char);
static void destroy_list(ll_node_x **head);
static ll_node_x *reverse_list(ll_node_x *head);
static void print_list(const ll_node_x *head);

static ll_node_x *create_list(char last_char)
{
  char c = 'a';
  ll_node_x *head = NULL;
  ll_node_x *tail = NULL;
  ll_node_x *temp = NULL;
  bool failure = false;

  while((c <= last_char) && (c <= 'z'))
  {
    //allocate and set the node data
    temp = (ll_node_x *)malloc(sizeof(*temp));
    if(NULL == temp)
    {
      printf("Oops ... failed to alloc %d bytes!\n",
	     sizeof(*temp));
      failure = true;
      break; //out of while loop
    }
    temp->data = c;
    temp->next = NULL;
    
    //if first node, remember it as head
    if(NULL == head)
    {
      head = temp;
    }

    //store tail to easily add new nodes at the end
    if(NULL != tail)
    {
      tail->next = temp;
    }
    tail = temp;

    //get next character
    c++;
  
  }//end of while

  //cleanup on failure, do not return partial lists
  if(true == failure)
  {
    destroy_list(&head);
  }

  return (head);
}

static void destroy_list(ll_node_x **head)
{
  ll_node_x *current = NULL;
  ll_node_x *temp = NULL;

  if(NULL != head)
  {
    //loop through and free each element
    current = *head;
    while(NULL != current)
    {
      temp = current->next;
      //free(current);
      current = temp;
    }
    *head = NULL; //set to null to avoid re-use
  }
  return;
}

static ll_node_x *reverse_list(ll_node_x *head)
{
  ll_node_x *current = head;
  ll_node_x *new_head = NULL;
  ll_node_x *temp = NULL;

  while(NULL != current)
  {
    //remember next ptr of current node as we will overwrite it
    temp = current->next;

    //add current node as head of new list
    current->next = new_head;
    new_head = current;

    //move to previously remembered next ptr
    current = temp;
  }
  return (new_head);
}

static void print_list(const ll_node_x *head)
{
  const ll_node_x *current = head;
  while(NULL != current)
  {
    printf("%c->", current->data);
    current = current->next;
  }
  printf("NULL\n");
  
  return;
}

int main()
{
  ll_node_x *head = NULL;

  head = create_list('e');
  assert(NULL != head);

  printf("Before reversal ...\n");
  print_list(head);

  head = reverse_list(head);
  assert(NULL != head);

  printf("After reversal ...\n");
  print_list(head);

  destroy_list(&head);
  assert(NULL == head);

  return 0;
}
