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
 
   node *head,*tail;
   
   int val;
   int index;
public:
    skip_list();
    node* get_head();
    node* find(long); //if not found return null, else return the node itself.
    node *find_prev(long);
    void insert(long,long); 
    void print_base_level();
    void print_list();
    void print_node(node*);
    //long get_offset(node*);
};
