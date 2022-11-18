#include<iostream>
#include<unordered_map>
#include <string>
using namespace std;

struct TrieNode
{
    unordered_map<char, TrieNode*> children;
    bool word_end=false;
};

class Tries
{
    public:
        TrieNode *root;
    public:
        Tries()
        {
            this->root = new TrieNode;
        }
    
    public:
        void insert_word(string word)
        {
            
            TrieNode*dummy = this->root;
            for(auto var : word)
            {
                if(dummy->children.find(var)==dummy->children.end())
                {
                    dummy->children[var] = new TrieNode;
                    dummy = dummy->children[var];
                }
                else
                {
                    dummy = dummy->children[var];  
                }
            }
            dummy->word_end=true;
        }

    public:
        void display(string a,struct TrieNode*root)
        {
            if((root->word_end))
            {
                cout<<a;
                printf("\n");
                return;
            }
            for(auto var: root->children)
            {
                
                display(a+var.first,var.second);
            }
        }
};


int main()
{

    printf("Enter Name to be entered: ");
    string name;
    cin >> name;
    Tries*obj = new Tries();
    
    obj->insert_word(name);
    obj->display("",obj->root);

    obj->insert_word("Adam");
    obj->display("",obj->root);


    

}