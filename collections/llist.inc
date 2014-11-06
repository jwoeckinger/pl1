   define struct 1 _llist, /* the list */
          2 head ptr,
          2 current ptr,
          2 cmp entry(ptr,ptr)returns(bin fixed(15));
   define struct 1 _node,
          2 next ptr,
          2 * bit(0);

   ll_init: proc(list);
     dcl list type _llist;
     list.current, list.head = null;
   end ll_init;

   /* inserts new item at "head". re-positions "current" */
   ll_add: proc(list);
     dcl list type _llist;
     dcl 1 x based(list),
           2 nx ptr;
     list.head->nx = list.current;
     list.current = list.head;
   end ll_add;

   /* re-position "current" to "head" */
   ll_get_head: proc(list);
     dcl list type _llist;
     list.current = list.head;
   end ll_get_head;

   ll_get_next: proc(list);
     dcl list type _llist;
     dcl 1 x based(list),
           2 nx ptr;
     list.current = list.current->nx;
   end ll_get_next;

   /* removes "head" node, may only be applied to "head", has to be
      called before "free" */
   ll_remove_head: proc(list) suppress(unref);
     dcl list type _llist;
     dcl 1 x based(list),
           2 nx ptr;
     if list.current <> list.head
     then $trace("ll_remove applied <> head");
     list.head = list.current->nx;          /* head neu setzen */
   end ll_remove_head;

   /* gets node for key, iterates sequentially (performance depends
      on number of elements!) */
   ll_get_keyed: proc(list, key) returns(bin fixed(15));
     dcl list type _llist;
     dcl key ptr;
     call ll_get_head(list);
     do while(list.current ^= null());
       if 0 = list.cmp(list.current, key)
       then
         return(0);
     end;
     return(1);
   end ll_get_keyed;                             
