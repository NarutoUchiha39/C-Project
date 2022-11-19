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
        unordered_map<string, long long int> PhoneBook;
        
    public:
        Tries()
        {
            this->root = new TrieNode;
        }
    public:
        void new_PhoneBook()
        {
            this->PhoneBook["Anirudha"] = 9820042597;
            this->PhoneBook["Adam"] = 9820042590;
            this->PhoneBook["Chutiya"] = 9999999999;
            this->PhoneBook["Naruto"] = 9820042599;
            this->PhoneBook["Adom"] = 0;
        }
    public:
        void insert(string word,long long int number)
        {

            this->PhoneBook[word] = number;
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
        void display_all_Names(string name,struct TrieNode*root)
        {
            if(root->word_end==true)
            {
                cout<<"Name: "<<name<<"\n";
                cout<<"Phone Number: "<<this->PhoneBook[name];
                cout<<"\n\n";
            }

            for(auto i: root->children)
            {
                display_all(name+i.first,root->children[i.first]);
            }
        }

    public:
        void search(string name)
        {
            TrieNode*head = this->root;
            for(auto i: name)
            {
                if(head->children.find(i)!=head->children.end())
                {
                    head = head->children[i];
                }
                else
                {
                    printf("Sorry the name you are seaching for doesnt exist!!\n");
                    return;
                }
            }

            if(head->word_end==true)
            {
                cout<<"Name: "<<name<<" Phone Number: "<<this->PhoneBook[name];
                return;
            }
            else
            {
                printf("Sorry the name you are seaching for doesnt exist!!\n");
                return;  
            }
        }
        void display_all(string name, struct TrieNode*root)
        {
            if(root->word_end==true)
            {
                cout<<"Name: "<<name<<"\n";
                cout<<"Phone Number: "<<this->PhoneBook[name];
                cout<<"\n\n";
            }

            for(auto i: root->children)
            {
                display_all(name+i.first,root->children[i.first]);
            }
        }
        void start_with_search(string name)
        {
            TrieNode*head = this->root;
            for(auto i:name)
            {
                if(head->children.find(i)!=head->children.end())
                {
                    head = head->children[i];
                }

                else
                {
                    cout<<"No name starts with "<<name;
                    return;
                }
            }
            cout<<"All the Names that start with "<<name<<" are: \n\n";
            this->display_all(name,head);
            
        }

        bool regex_search(int index,string name,struct TrieNode*head)
        {
            for(int i=index;i<name.size();i++)
            {
                if(name[i]=='.')
                {
                    for(auto j:head->children)
                    {
                        if(regex_search(i+1,name,head->children[j.first])==true)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                else
                {
                    if(head->children.find(name[i])!=head->children.end())
                    {
                        head = head->children[name[i]];
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            if(head->word_end==true)
            {
                return true;
            }
            else{return false;};


        }
};


int main()
{
    // Driver Code to use Phone Book
    Tries*obj = new Tries();
    obj->new_PhoneBook();

    // Inserting Words from hash map into tries
    for(auto i: obj->PhoneBook)
    {
        obj->insert(i.first,i.second);
    }
   
}