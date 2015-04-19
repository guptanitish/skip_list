struct node
{
  long val,offset;
  node *next,*down,*prev,*up;
  node(long i,long o)
  {
    val = i;
    offset = o;
    next=down=prev=up=NULL;
  }
};

//must use short? instead of long for offset
class skip_list {

private:
  
   node *bottom_head = new node(LONG_MIN,0);
   node *bottom_tail = new node(LONG_MAX,0);
   node *head,*tail;
   
   int val;
   int index;
public:
    skip_list();
    node* get_head();
    node* find(long); //if not found return null, else return the node itself.
    node *find_prev(long);
    //void insert(long); 
    //long get_offset(node*);
};
