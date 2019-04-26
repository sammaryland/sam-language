#include "dll.h"

struct node{
  void *value;
  struct node *next;
  struct node *prev;
};

typedef struct node node;

struct dll {
  struct node *head;
  struct node *tail;
  int size;
  void (*display)(void *, FILE *);
  void (*free)(void *);
};

node *newDLLNode();

DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *)){
  DLL *items = malloc(sizeof(DLL));
  assert(items != 0);
  items -> head = 0;
  items -> tail = 0;
  items -> size = 0;
  items -> display = d;
  items -> free = f;
  return items;
}

node *newDLLNode(){
  node *n = malloc(sizeof(node));
  n -> value = 0;
  n -> next = 0;
  n -> prev = 0;
  return n;
}

void insertDLL(DLL *items,int index,void *value){
  assert(index >= 0 && index <= items -> size);
  int i;
  node *new_node, *temp, *temp1;
  new_node = newDLLNode();
  new_node -> value = value;
  if (index == 0){
    if (items -> head == 0){
      items -> head = new_node;
      items -> tail = new_node;
    }
    else{
      new_node -> next = items -> head;
      items -> head -> prev = new_node;
      items -> head = new_node;
    }
  }
  if (index == items -> size){
    if (index == 0){
      items -> head = new_node;
      items -> tail = new_node;
    }
    else{
      items -> tail -> next = new_node;
      new_node -> prev = items -> tail;
      items -> tail = new_node;
    }
  }
  else{
    if (items -> head == 0){
      new_node -> next = 0;
      items -> head = new_node;
      items -> tail = new_node;
    }
    else{
      double test = (double)sizeDLL(items) / 2;
      if (index > test){
        temp = items -> tail;
        for (i = sizeDLL(items); i > index; i--){
          temp = temp -> prev;
        }
        temp1 = temp -> next;
        temp -> next = new_node;
        new_node -> prev = temp;
        new_node -> next = temp1;
        temp1 -> prev = new_node;
      }
      else{
        temp = items -> head;
        for (i = 0; i < index - 1; i++){
          temp = temp -> next;
        }
        temp1 = temp -> next;
        temp -> next = new_node;
        new_node -> prev = temp;
        new_node -> next = temp1;
        temp1 -> prev = new_node;
      }
    }
  }
  items -> size += 1;
}

void *removeDLL(DLL *items,int index){
  assert(items -> size > 0 && index >= 0 && index < items -> size);
  if (index == 0){
    node *temp = items -> head;
    node *val = temp -> value;
    if (temp != 0){
      if (temp -> next != 0){
        temp -> next -> prev = 0;
      }
      items -> head = temp -> next;
      items -> size -= 1;
      if (items -> size == 0){
        items -> head = 0;
        items -> tail = 0;
      }
      free(temp);
      return val;
    }
  }
  if (index == sizeDLL(items) - 1){
    node *temp = items -> tail;
    void *val = temp -> value;
    if (items -> head != 0){
      if (items -> tail != 0){
        temp -> prev -> next = 0;
        items -> tail = temp -> prev;
      }
      else{
        items -> head = 0;
      }
      items -> size -= 1;
    }
    if (items -> size == 0){
      items -> head = 0;
      items -> tail = 0;
    }
    free(temp);
    return val;
  }
  else{
    double test = (double)sizeDLL(items) / 2;
    if (index > test){
      node *temp = items -> tail;
      for (int i = sizeDLL(items); i > index + 1; i--){
        temp = temp -> prev;
      }
      void *val = temp -> value;
      node *prev = temp -> prev;
      node *next = temp -> next;
      if (prev == 0){
        items -> head = next;
        next -> prev = 0;
      }
      else if (next == 0){
        items -> tail = prev;
        prev -> next = 0;
      }
      else{
        prev -> next = next;
        next -> prev = prev;
      }
      items -> size -= 1;
      if (items -> size == 0){
        items -> head = 0;
        items -> tail = 0;
      }
      free(temp);
      return val;
    }
    else{
      node *temp = items -> head;
      for (int i = 0; i < index; i++){
        temp = temp -> next;
      }
      void *val = temp -> value;
      node *prev = temp -> prev;
      node *next = temp -> next;
      if (prev == 0){
        items -> head = next;
        next -> prev = 0;
      }
      else if (next == 0){
        items -> tail = prev;
        prev -> next = 0;
      }
      else{
        prev -> next = next;
        next -> prev = prev;
      }
      items -> size -= 1;
      if (items -> size == 0){
        items -> head = 0;
        items -> tail = 0;
      }
      free(temp);
      return val;
    }
  }
}

void unionDLL(DLL *recipient,DLL *donor){
  if (sizeDLL(donor) != 0){
    recipient -> tail -> next = donor -> head;
    donor -> head -> prev = recipient -> tail;
    recipient -> tail = donor -> tail;
    donor -> head = recipient -> head;
    recipient -> size += donor -> size;
  }
  donor -> size = 0;
}

void *getDLL(DLL *items,int index){
  assert(index >= 0 && index < items -> size);
  if (index == 0){
    void *val = items -> head -> value;
    return val;
  }
  if (index == (items -> size) - 1){
    void *val = items -> tail -> value;
    return val;
  }
  else{
    double test = (double)sizeDLL(items) / 2;
    if (index > test){
      node *temp = items -> tail;
      for (int i = sizeDLL(items); i > index + 1; i--){
        temp = temp -> prev;
      }
      return temp -> value;
    }
    else{
      node *temp = items -> head;
      for (int i = 0; i < index; i++){
        temp = temp -> next;
      }
      return temp -> value;
    }
  }
}

void *setDLL(DLL *items,int index,void *value){
  assert(index >= 0 && index <= items -> size);
  if (index == sizeDLL(items)){
    insertDLL(items, sizeDLL(items), value);
    return 0;
  }
  if (index == 0){
    void *val = items -> head -> value;
    items -> head -> value = value;
    return val;
  }
  if (index == sizeDLL(items) - 1){
    void *val = items -> tail -> value;
    items -> tail -> value = value;
    return val;
  }
  else{
    double test = (double)sizeDLL(items) / 2;
    if (index > test){
      node *temp = items -> tail;
      for (int i = sizeDLL(items); i > index + 1; i--){
        temp = temp -> prev;
      }
      void *val = temp -> value;
      temp -> value = value;
      return val;
    }
    else{
      node *temp = items -> head;
      for (int i = 0; i < index; i++){
        temp = temp -> next;
      }
      void *val = temp -> value;
      temp -> value = value;
      return val;
    }
  }
}

int sizeDLL(DLL *items){
  return items -> size;
}

void displayDLL(DLL *items,FILE *fp){
  fprintf(fp, "{{");
  for (int i = 0; i < sizeDLL(items); i++){
    items -> display(getDLL(items, i), fp);
    if (i != sizeDLL(items) - 1){fprintf(fp, ",");}
  }
  fprintf(fp, "}}");
}

void displayDLLdebug(DLL *items,FILE *fp){
  if (items -> size == 0){
    fprintf(fp, "head->{{}},tail->{{}}");
  }
  else{
    fprintf(fp, "head->{{");
    for (int i = 0; i < sizeDLL(items); i++){
      items -> display(getDLL(items, i), fp);
      if (i != sizeDLL(items) - 1){fprintf(fp, ",");}
    }
    fprintf(fp, "}},tail->{{");
    node *t = items -> tail;
    if (t != 0){items -> display(t -> value, fp);}
    fprintf(fp, "}}");
  }
}

void freeDLL(DLL *items){
  if (items -> size != 0){
    node *temp = items -> head;
    for(int i = 0; i < sizeDLL(items); i++){
      node *temp1 = temp;
      temp = temp -> next;
      if (items -> free != 0){items -> free(temp1 -> value);}
      free(temp1);
    }
  }
  free(items);
}
