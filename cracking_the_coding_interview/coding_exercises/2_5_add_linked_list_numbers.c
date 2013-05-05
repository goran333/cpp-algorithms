node * addLinkedListNumbers(node *head1, node *head2)
{
  //check for nulls on head1, head2

  //create numbers from linked list elements

  node1 = head1;
  i = 0;
  number1 = 0;
  while(NULL != node1)
    {
      number1 = (node1->data) + (number1 * 10^i);
      node1 = node1->next;
    }


}
