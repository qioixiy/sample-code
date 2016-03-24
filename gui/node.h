
#ifndef _NODE_H_
#define _NODE_H_

struct node {
    struct node* parents;
    struct node* child;
    struct node* sibling;
};

#endif
