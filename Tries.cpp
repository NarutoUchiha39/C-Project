#include<iostream>
#include<unordered_map>
#include <string>
#include <fstream>
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
            ifstream fin;
            fin.open("phone-list.csv");
            string line;
            string name;
            string number;
            while (getline(fin, line)) 
            {
                getline ( fin, name, ',' );
                getline ( fin, number, ',' );
                this->PhoneBook[name]=stoll(number);
            }
        
            fin.close();
            
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
    
    cout<<"\nPress 1 to insert names into Phone Book\nPress 2 to view all names in Phone Book\nPress 3 to search for a name\nPress 4 to search for names begining with a particular sequence";
    cout<<"\nPress 5 to perform a regex search\nPress 6 to exit\n";
    while (true)
    {
        int choice;
        cout<<"Enter choice: ";
        cin>>choice;
        int flag;
        string name;
        string seq;
        bool val;
        cout<<"\n";
        switch (choice)
        {
        case 1:
            cout<<"Enter Name to inserted: ";
            cin>>name;
            cout<<"Enter Number: ";
            long long number;
            cin>>number;
            obj->insert(name,number);
            cout<<"\n";
            break;
        case 2:
            obj->display_all_Names("",obj->root);
            break;
        case 3:
            cout<<"Enter name to be searched for: ";
            cin>>name;
            obj->search(name);
            cout<<"\n";
            break;
        case 4:
            cout<<"Enter begining sequence for a name to be searched for: ";
            cin>>seq;
            obj->start_with_search(seq);
            cout<<"\n";
            break;
        case 5:
            cout<<"Enter name with . where any character can be matched: ";
            cin>>name;
            val=obj->regex_search(0,name,obj->root);
            if(val==true)
            {
                cout<<"The name exists in the Phone Book";
            }
            else
            {
                cout<<"The name doesnt exist in the Phone Book";
            }
            cout<<"\n";
            break;
        case 6:
            flag=1;
            break;

        default:
            cout<<"Please enter a valid choice";
            cout<<"\n";
            break;
        }
        if(flag==1)
        {
            break;
        }
    }

    
    
    
}