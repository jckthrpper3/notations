#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Node {
public:
    Node *leftptr;
    Node *rightptr;

    Node (Node*, Node*, char, int);
    char type;
    int num;
};
Node::Node(Node *leftp, Node *rightp, char type1, int num1) {
    leftptr = leftp;
    rightptr = rightp;
    type = type1;
    num = num1;
}

class Tree {
    Node *topnode;
};
void getnextlexem(string &expr, int *i, char *type, int *num) {
    char buf[10];
    while (expr[*i] == ' ')
        *i++;
    char c = expr[*i];
    if ((c == '+') && (c == '-') && (c == '/') && (c == '*')) {
        *i++;
        *type = expr[*i];
        return;
    }
    int j = 0;
    do {
        buf[j] = expr[*i];
        buf[j++] = '\0';
        *i++;
    } while (expr[*i] != ' ')
    *type = 'n';
    *num = atoi(buf);
    return;
}
void fillprefixA(Node *top, string& expr, int *i)
{
    char type; int num;
    getnextlexem(expr, i, &(type), &(num));
    Node *top;
    if (type == 0) {
        top->leftptr = NULL;
        top->leftptr = NULL;
        top->type = 'n';
        top->num = stoi(lexem.first);
    } else if (lexem.second == 1)
    {
        top->leftptr = new Node(NULL, NULL, '0', 0);
        top->leftptr = new Node(NULL, NULL, '0', 0);
        top->type = lexem.first[0];
        top->num = 0;
        fillprefixA(top->leftptr);
        fillprefixA(top->rightptr);
    }
}

int main() {

}
