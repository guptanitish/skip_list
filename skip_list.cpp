#include <bits/stdc++.h>
#include "skip_list.h"
using namespace std;

//put this in utils
int coinToss()
{
   return rand()%2;
}

skip_list::skip_list()
{
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
	return temp;
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
  node *prev = find_prev(long val);
  
  if(prev->next->val==val) //if node exists
  {
    //update the offset pointers.. 
  }
  else
  {
    node *new_node = new node(val,offset);
    new_node->next = prev->next;
    new_node->prev=prev;
    prev->next=new_node;
    
    //promote the node up.
    node *current_level_head = bottom_head;
    node *current_level_tail = bottom_tail;
    while(coinToss)
    {
      node *temp = new_node;
      //find the closest upper level node.
      while(temp)
      {
	if(temp->up)
	{
	  temp=temp->up;
	  break;
	}
	temp=temp->prev;
      }
      //if the upper level exists
      if(temp)
      {
	
	node *new_node_upper =  new node(val,offset);
	new_node_upper->next = temp->next;
	new_node_upper->prev=temp;
	temp->next=new_node_upper;
	new_node_upper->down=new_node;
	new_node->up=  new_node_upper;
      }
      else
      {
	node *new_node_upper =  new node(val,offset);
	node *new_node_upper_head =  new node(LONG_MIN,0);
	node *new_node_upper_tail =  new node(LONG_MAX,0);
	
	new_node_upper_head->next = new_node_upper;
	new_node_upper_head->down = current_level_head;
	
	new_node_upper->prev = new_node_upper_head;
	new_node_upper->next = new_node_upper_tail;
	new_node_upper->down = new_node;
	new_node->up = new_node_upper;
	
	new_node_upper_tail->prev = new_node_upper;
	new_node_upper_tail->down = current_level_tail;
	
	current_level_head->up=new_node_upper_head;
	current_level_tail->up = new_node_upper_tail;
	
	head = new_node_upper_head;
	tail = new_node_upper_tail;
	
      }
    }
  }
    
}
//delete this:
node* skip_list::get_head()
{
  return head;
}
int main()
{
  skip_list s;
  node *temp = s.find(2);
  if(temp)
    cout<<temp->val<<endl;
  else
    cout<<"Nahi hai be"<<endl;
  temp = s.find_prev(2);
  cout<<temp->val<<endl;
  
  //cout<<s.index;
  return 0;
}