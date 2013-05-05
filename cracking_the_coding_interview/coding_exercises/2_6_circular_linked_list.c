//O(N*N) solution
Node *findHeadOfCircle(const Node *head)
{
  //check for null

  //two pointers, double loop

  p1 = head;
  p2 = head->next;
  Node *circleHead = NULL;

  while((NULL != p1) && (NULL != circleHead))
    {
      p2 = p1->next;
      while(NULL != p2)
	{
	  if((NULL != p2->next) && (p1->next == p2->next))
	    {
	      circleHead = p1->next;
	      break; //from inner while
	    }
	  p2 = p2->next;
	}
      p1 = p1->next;
    }

  return circleHead;
}


