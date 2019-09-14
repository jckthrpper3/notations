#include <iostream>
#include <string>
#include <vector>

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define NUM 0

#define PREFIX 0
#define INFEX 1
#define POSTFIX 2

using namespace std;

class node {
public:
    node *leftchild;
    node *rightchild;
    node *parent;

    int type;
    int value;
    char cvalue;

    ~node();
};
node::~node() {
    if (leftchild != NULL)
        delete leftchild;
    if (rightchild != NULL)
        delete rightchild;
}
class lexems {
public:
    vector<int> lexem;
    vector<int> value;
};
lexems* CreateLexems(string str) {
    lexems *lex = new lexems;
    int x;
    bool ConstructingInt = false;
    for (int i=0; i < str.size(); i++) {
        if (('0' <= str[i]) && (str[i] <= '9')) {
            if (!ConstructingInt) {
                (lex->lexem).push_back(NUM);
                ConstructingInt = true;
                x = 0;
            }
            x = x*10 + str[i]-'0';
        }
        else if (ConstructingInt) {
            (lex->value).push_back(x);
            ConstructingInt = false;
        }
        switch (str[i]) {
        case '+':
            (lex->lexem).push_back(ADD);
            (lex->value).push_back(0);
            break;
        case '-':
            (lex->lexem).push_back(SUB);
            (lex->value).push_back(0);
            break;
        case '*':
            (lex->lexem).push_back(MUL);
            (lex->value).push_back(0);
            break;
        case '/':
            (lex->lexem).push_back(DIV);
            (lex->value).push_back(0);
            break;
        }
    }
    if (ConstructingInt)
        (lex->value).push_back(x);
    return lex;
}

node* CreateHeap(lexems* lex, int *beg, int notation){
    node* Node = new node;
    switch(notation) {
    case PREFIX:
        if ((lex->lexem)[*beg] == NUM) {
            Node->leftchild = NULL;
            Node->rightchild = NULL;
            Node->type = NUM;
            Node->value = (lex->value)[*beg];
            return Node;
        }
        Node->type = (lex->lexem)[*beg];
        Node->value = 0;
        Node->leftchild = CreateHeap(lex, beg, PREFIX);
        Node->rightchild = CreateHeap(lex, beg, PREFIX);
        return Node;
    }
}
void TranslateHeap(node *top, lexems* lex, int notation) {
    switch(notation) {
    case PREFIX:
        if (top->type == NUM) {
            (lex->lexem).push_back(NUM);
            (lex->value).push_back(top->value);
            return;
        }
        (lex->lexem).push_back(top->type);
        (lex->value).push_back(0);

        TranslateHeap(top->leftchild, lex, PREFIX);
        TranslateHeap(top->rightchild, lex, PREFIX);
        return;
    }
}
int main() {
    string x;
    int i=0;
    getline(cin, x);
    lexems *lex = CreateLexems(x);
    node *Node = CreateHeap(lex, &i, PREFIX);
    delete lex;
    TranslateHeap(Node, lex, PREFIX);
    delete Node;

    for(int i=0; i < (lex->lexem).size(); i++)
        cout << (lex->lexem)[i] << "  "<< (lex->value)[i] << '\n';
    return 0;
}
