//O(N*N) solution
bool isCircular(const Node *head)
{
  //check for null

  p_slow = head;
  p_fast = head;

  while(1)
  {
     //move slow ptr by 1
     p_slow = p_slow->next;
     if(NULL == p_slow)
        break; //found the end of list - should happen only on 1 element list

     //move fast ptr by 2
     p_fast = p_fast->next;
     if(NULL == p_fast)
        break; //found the end of list
     p_fast = p_fast->next;
     if(NULL == p_fast)
        break; //found the end of list

     if(p_fast == p_slow)
     {
        is_circular = true;
        break;
     }
  }



  return (is_circular);
}

Node *findHeadOfCircle(const Node *head)
{
  //check for null

  //two pointers, double loop

  p_slow = head;
  p_fast = head;

  while(1)
  {
     //move slow ptr by 1
     p_slow = p_slow->next;
     if(NULL == p_slow)
        break; //found the end of list - should happen only on 1 element list

     //move fast ptr by 2
     p_fast = p_fast->next;
     if(NULL == p_fast)
        break; //found the end of list
     p_fast = p_fast->next;
     if(NULL == p_fast)
        break; //found the end of list

     if(p_fast->next == p_slow->next)
     {
        is_circular = true;
        break;
     }
  }

  p_slow = p_slow->next;
  p_fast = p_fast->next->next;

    



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


