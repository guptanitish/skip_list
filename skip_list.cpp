#include <bits/stdc++.h>
#include "skip_list.h"
using namespace std;

//put this in utils
int coinToss()
{
  return 0;
   //return rand()%2;
}

skip_list::skip_list()
{
  node *bottom_head = new node(LONG_MIN,0);
  node *bottom_tail = new node(LONG_MAX,0);
  
  bottom_head->next = bottom_tail;
  bottom_tail->prev=bottom_head;
  
  head=bottom_head;
  tail = bottom_tail;
}

node* skip_list::find(long val)
{
  node *temp=head;
  
  while(temp)
  {
    if(temp->next->val<val)
    {
      temp=temp->next;
    }
    else if(temp->next->val==val)
    {
      if(temp->down)
	temp=temp->down;
      else
	return temp->next;
    }
    else
    {
      temp=temp->down;
    } 
  }
  return temp;
}

node* skip_list::find_prev(long val)
{
  node *temp=head;
  
  while(temp)
  {
    if(temp->next->val<val)
    {
      temp=temp->next;
    }
    
    else	//current val is equal or lesser than next val
    {
      if(temp->down)
	temp=temp->down;
      else
	return temp;
    } 
  }
  return temp;
}

void skip_list::insert(long val,long offset)
{
  //find place to insert
  node *prev = find_prev(val);
  
  if(prev->next->val==val) //if the value already exists
  {
    //update the offset pointers.. 
  }
  else
  {
    node *new_node = new node(val,offset);
    new_node->next = prev->next;
    new_node->prev=prev;
    prev->next=new_node;
    new_node->next->prev=new_node;
    
    //promote the node up.
    node *node_to_copy = new_node;
    while(coinToss())
    {
      node *temp = node_to_copy;
      //find the closest upper level node.
      while(temp)
      {
	if(temp->up)
	{
	  //temp=temp->up;
	  break;
	}
	if(temp->val==LONG_MIN)
	    break;
	temp=temp->prev;
      }
      node *new_node_upper =  new node(val,offset);
      //if the upper level exists
      if(temp->up)
      {
	temp = temp->up;
	
	new_node_upper->next = temp->next;
	new_node_upper->prev=temp;
	new_node_upper->next->prev = new_node_upper;
	temp->next=new_node_upper;
	
      }
      else //create new level
      {
	//create 3 new nodes - 2 sentinel nodes.
	//node *new_node_upper =  new node(val,offset);
	node *new_node_upper_head =  new node(LONG_MIN,0);
	node *new_node_upper_tail =  new node(LONG_MAX,0);
	
	new_node_upper_head->next = new_node_upper;
	new_node_upper_head->down = head;
	
	new_node_upper->prev = new_node_upper_head;
	new_node_upper->next = new_node_upper_tail;
	
	new_node_upper_tail->prev = new_node_upper;
	new_node_upper_tail->down = tail;
	
	head->up = new_node_upper_head;
	tail->up = new_node_upper_tail;
	
	head = new_node_upper_head;
	tail = new_node_upper_tail;
	
      }
      new_node_upper->down=node_to_copy;
      node_to_copy->up =  new_node_upper;
      node_to_copy = new_node_upper;
    }
  }
    
}
//delete this:
node* skip_list::get_head()
{
  return head;
}

void skip_list::print_base_level()
{
  //find base level head
  node *temp=head;
  while(temp->down)
    temp=temp->down;
  //temp=temp->next; //ignoring the sentinel
  while(temp->next)
  {
    cout<<"("<<temp->val<<","<<temp->offset<<")"<<"\t";
    temp=temp->next;
  }
}
int main()
{
  skip_list s;
  node *temp = s.find(2);
  if(temp)
    cout<<temp->offset<<endl;
  else
    cout<<"Nahi hai be"<<endl;
 
  s.insert(2,3);
  temp = s.find(4);
  
  if(temp)
    cout<<temp->offset<<endl;
  else
    cout<<"Nahi hai be"<<endl;
  
  node* temp1 = s.find(2);
  s.insert(2,3);
  s.insert(3,3);
  s.insert(1,3);
  s.insert(5,3);
  s.insert(5,3);
  if(temp1)
  {  
    cout<<temp1->val<<endl;
    cout<<temp1->offset<<endl;
  }
  else
    cout<<"Nahi hai be"<<endl;
  //cout<<s.index;
    s.print_base_level();
  return 0;
}