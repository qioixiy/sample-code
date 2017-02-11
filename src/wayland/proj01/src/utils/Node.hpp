
#ifndef _NODE_HPP_
#define _NODE_HPP_

#include <string>

using namespace std;

/*   sibling
 * o (root)
 * |
 c* o--o--o--o--o
 h* |  |  |  |
 i* o  o  o  o--o
 l* |  |
 d* o  o--o--o--o
 * |  |  |     |
 * o  o  o--o  o
 */

class Node
{
public:
    Node();
    virtual ~Node() {}

    Node *first_sibling();
    Node *last_sibling();
    Node *prev();
    Node *next();
    int get_sibling_depth();

    Node *first_child()
    {
        return child_head;
    }
    Node *last_child()
    {
        return child_tail;
    }
    Node *parent()
    {
        return parent_node;
    }

    void link_this_to_parent_last (Node *parent);
    void link_this_to_parent_first(Node *parent);
    void link_this_to_sibling_next(Node *sibling);
    void link_this_to_sibling_prev(Node *sibling);
    void unlink();
    void SetName(const char *name)
    {
        this->name = name;
    }
    string get_name()
    {
        return name;
    }

    void dump();

protected:
    Node *parent_node;
    Node *child_head;
    Node *child_tail;
    Node *next_sibling;
    Node *prev_sibling;
    string name;
};

#endif
