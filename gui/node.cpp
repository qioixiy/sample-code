
#include <cstdio>
#include <cmath>
#include <queue>

#include "node.hpp"

Node::Node()
{
    parent_node = NULL;
    child_head = NULL;
    child_tail = NULL;
    next_sibling = NULL;
    prev_sibling = NULL;
}

/* Returns first sibling in 'this' node's sibling list */
Node *Node::first_sibling(void)
{
    if (parent_node == NULL)  
        return this;            /* root node has no siblings */
    else
        return parent_node->child_head;
}

/* Returns next sibling in 'this' node's sibling list */
Node *Node::next(void)
{
    return next_sibling;
}

/* Returns prev sibling in 'this' node's sibling list */
Node *Node::prev(void)
{
    return prev_sibling;
}

/* Returns last sibling in 'this' node's sibling list */
Node *Node::last_sibling(void)
{
    if (parent_node == NULL)
        return this;            /* root node has no siblings */
    else
        return parent_node->child_tail;
}

/* Links as last child of parent */
void Node::link_this_to_parent_last(Node *new_parent)
{
    if ( new_parent->child_tail == NULL ) {   /* parent has no children */
        new_parent->child_head = this;
        new_parent->child_tail = this;
        this->parent_node      = new_parent;
    }
    else {                      /* parent has children */
        new_parent->child_tail->next_sibling = this;
        this->prev_sibling                   = new_parent->child_tail;
        new_parent->child_tail               = this;
        this->parent_node                    = new_parent;
    }
}

/* Links as first child of parent */
void Node::link_this_to_parent_first(Node *new_parent)
{
    if ( new_parent->child_head == NULL ) { /* parent has no children */
        new_parent->child_head               = this;
        new_parent->child_tail               = this;
        this->parent_node                    = new_parent;
    }
    else {                      /* parent has children */
        new_parent->child_head->prev_sibling = this;
        this->next_sibling                   = new_parent->child_head;
        new_parent->child_head               = this;
        this->parent_node                    = new_parent;
    }
}

void Node::link_this_to_sibling_next( Node *sibling )
{
    if ( sibling->next_sibling == NULL ) { /* node has no next sibling */
        sibling->next_sibling  = this;
        this->prev_sibling     = sibling;

        /* This was the parent's last child, so update that as well */
        if ( sibling->parent_node  != NULL ) {
            sibling->parent_node->child_tail = this;
        }
    }
    else {                      /* node already has a next sibling */
        sibling->next_sibling->prev_sibling = this;
        this->next_sibling                  = sibling->next_sibling;
        sibling->next_sibling               = this;
        this->prev_sibling                  = sibling;
    }

    this->parent_node = sibling->parent_node;
}

void Node::link_this_to_sibling_prev( Node *sibling )
{
    if ( sibling->prev_sibling == NULL ) { /* node has no prev sibling */
        sibling->prev_sibling  = this;
        this->next_sibling     = sibling;

        /* This was the parent's first child, so update that as well */
        if ( sibling->parent_node  != NULL ) {
            sibling->parent_node->child_head = this;
        }
    }
    else {                      /* node already has a prev sibling */
        sibling->prev_sibling->next_sibling = this;
        this->prev_sibling                  = sibling->prev_sibling;
        sibling->prev_sibling               = this;
        this->next_sibling                  = sibling;
    }

    this->parent_node = sibling->parent_node;
}

void   Node::unlink( void )
{
    /* Unlink from prev sibling */
    if ( this->prev_sibling != NULL ) {
        this->prev_sibling->next_sibling = this->next_sibling;
    }
    else {        /* No prev sibling: this was parent's first child */
        this->parent_node->child_head = this->next_sibling;
    }

    /* Unlink from next sibling */
    if ( this->next_sibling != NULL ) {
        this->next_sibling->prev_sibling = this->prev_sibling;
    }
    else {         /* No next sibling: this was parent's last child */
        this->parent_node->child_tail = this->prev_sibling;
    }

    this->parent_node  = NULL;
    this->next_sibling = NULL;
    this->prev_sibling = NULL;
    this->child_head   = NULL;
    this->child_tail   = NULL;
}

int Node::get_sibling_depth()
{
    int ret = 0;

    Node* node = this->first_sibling();
    while((node != this) && (node = node->next()))
        ret++;

    return ret;
}

void Node::dump()
{
    queue<Node*> *q1 = new queue<Node*>();
    queue<Node*> *q2 = new queue<Node*>();
    q1->push(this);

    Node* node = this;
    while(!q1->empty()) {
        // pop->handle->push
        while(!q1->empty()) {
            // pop
            Node* n = q1->front(); q1->pop();

            // handle
            printf("%s[%d] ", n->get_name().c_str(), n->get_sibling_depth());

            // push
            Node* next_child = n->first_child();
            while (next_child) {
                q2->push(next_child);
                next_child = next_child->next();
            }
        }
        printf("\n");
        queue<Node*> *temp = q1;
        q1 = q2;
        q2 = temp;
    }
}
