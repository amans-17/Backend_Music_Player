#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cmath>
#include<time.h>

using namespace std;

int found=0;
struct Node                 //Node For Linked List
{
   string song;
   Node* next;
};

class List                  //class for Linked List
{
    public:
    Node* head=NULL;
    Node* tail=NULL;

    void add(string x)          //Addition of Nodes In Linked List
    {
        Node* temp=new Node;
        temp->song=x;
        temp->next=NULL;
        if(head==NULL)
        {
           head=temp;
           tail=temp;
           temp=NULL;
        }
        else
        {
            tail->next=temp;
            tail=temp;
        }
    }
    void display()              // Printing All Nodes Of Linked List
    {
        Node* temp=head;
        while(temp!=NULL)
        {
            cout<<temp->song<<endl;
            temp=temp->next;
        }
    }

    void deletelast()
    {
        Node* temp=head;
        Node* prev=head;
        while(temp->next!=NULL)
        {
            prev=temp;
            temp=temp->next;
        }
        tail=prev;
        prev->next=NULL;
        delete temp;
    }

    void deletesong(string k)
    {
        Node* temp=head;
        Node* prev=NULL;
        while(temp->song!=k)
        {
            prev=temp;
            temp=temp->next;
        }
        if(temp!=head)
        prev->next=temp->next;
        else
            head=temp->next;
            delete temp;
    }

    void swap(int a, int b)
    {
        Node* prevA=NULL;
        Node* prevB=NULL;;
        Node* currA=head;
        Node* currB=head;
        if(a==b)
            return;
         for(int i=1;i<a;i++)
        {

            prevA=currA;
            currA=currA->next;
        }

        for(int j=1;j<b;j++)
       {
           prevB=currB;
           currB=currB->next;
       }

        Node* temp=new Node;
        temp->next=currA->next;
        currA->next=currB->next;
        currB->next=temp->next;
        prevB->next=currA;
        prevA->next=currB;
    }
    int sizeofplaylist()
    {
        int count=0;
        Node*temp=head;
        while(temp!=NULL)
        {
            count++;
            temp=temp->next;
        }
        return count;
    }

    void shuffle()
    {
        int x=sizeofplaylist();
        int lower=1;
        int upper=x;
        srand(time(0));
        for(int i=1;i<50;i++)
        {
        int k1=(rand()%(upper-lower))+2;
        int k2=(rand()%(upper-lower))+2;
        if(abs(k1-k2)==1)
            continue;
        swap(k1,k2);
        }
    }

        void play()
        {
            Node* temp=head->next;
            head->next=NULL;
            tail->next=head;
            tail=head;
            head=temp;
        }
        bool iftop(string x)
        {
            if(head->song==x)
                return true;
            else
                return false;
        }

        void movetoend(string x)
        {
            Node* curr=head;
            Node* prev=NULL;
            while(curr->song!=x)
            {
                prev=curr;
                curr=curr->next;
            }
            prev->next=curr->next;
            curr->next=NULL;
            tail->next=curr;
            tail=curr;
        }
};
class node{                 //class for Trie data structure
    public:
        char info;
        string Song;
        class node* ptrs[256];
        node(){
            for(int i=0;i<256;i++){
                ptrs[i]=NULL;
            }
            info=NULL;
            Song="";
        }
};

void insertsong(string song,int pos,class node * root){
    if(song.length()==pos){
        root->Song=song;
        return;
    }
    if( root->ptrs[song[pos]]==NULL ){
        node *newnode = new node;
        newnode->info=song[pos];
        root->ptrs[song[pos]]=newnode;
        insertsong(song,pos+1,root->ptrs[song[pos]]);
    }
    else
        insertsong(song,pos+1,root->ptrs[song[pos]]);
}

void find(string key,int pos,node* root){
    if((key!=root->Song) && (root->ptrs[key[pos]]!=NULL))
        find(key,pos+1,root->ptrs[key[pos]]);
    else if(key==root->Song){
        found=1;
    }
}

void printeverything(node* root){
    for(int i=0;i<256;i++)
        if(root->ptrs[i]!=NULL){
            printeverything(root->ptrs[i]);
        }
    if(root->Song!="")
        cout<<" : "<<root->Song<<" "<<endl;
}

void recommend(string key,int pos, class node* root){
    if((key!=root->Song) && (root->ptrs[key[pos]]!=NULL)){
            recommend(key,pos+1,root->ptrs[key[pos]]);
    }
    else{
            printeverything(root);
    }
}

int main(){
    ifstream in("songs.txt");
    string song,current="",key;
    node *root;
    root = new node;
    while(in){
        getline(in, song);
        insertsong(song,0,root);   //trie is used here
    }
    in.close();
    int a;
    int flag=0;
    List L1;                     //object of class List
    ifstream Lin("songs.txt");
    string insong;
    while(getline(Lin,insong))
    {
        //getline(Lin, insong);
        L1.add(insong);
    }
    Lin.close();

    string s1,s2,s3,s4;
        while(flag==0)
    {
        cout<<endl<<"What would you like to do?\n"<<"1.Display the playlist\n"<<"2.Play the song at top of list\n"<<"3.Shuffle\n"<<"4.Select a specific song you want to play\n"<<"5.Delete song from playlist\n"<<"6.Search for a song\n"<<"7.Add new song to playlist\n"<<"8.Exit\n";
        cin>>a;
        cin.ignore();
        switch (a)
        {
    case 1:
        L1.display();
        break;
    case 2:
        cout<<endl<<"You are playing "<<L1.head->song;
        L1.play();
        break;
    case 3:
        L1.shuffle();
        cout<<endl<<"Playlist successfully shuffled, new playlist is:" << endl;
        L1.display();
        break;
    case 4:
        getline(cin, s1);
        find(s1,0,root);
        if (found==1)
        {
        L1.movetoend(s1);
        cout<<"Now playing "<<s1;
        found=0;
        }
        else
        {cout<<endl<<"Sorry, this song is not in the library, did you mean" << endl;
        recommend(s1,0,root);}
        break;
    case 5:
        getline(cin, s2);
        find(s2,0,root);
        if (found==1)
        {L1.deletesong(s2);
         cout<<"The song has been successfully deleted";
         found=0;}
         else
            cout<<"Oops! The song doesn't exist";
         break;

    case 6:
        getline(cin, s3);
        find(s3,0,root);
        if (found==1)
        {
            cout<<endl<<s3<<" exists in the library!";
            found=0;
        }
        else
            cout<<endl<<"Sorry, you don't have this song :(";
        break;
    case 7:
        getline(cin,s4);
        find(s4,0,root);
        if(found==1){
            cout << "Song is already present in your playlist" << endl;
        }
        else{
            insertsong(s4,0,root);
            ofstream out("songs.txt",ios::app);
            out << s4;
            out.close();
            L1.add(s4);
            cout<<"Song successfully added"<<endl;
        }
        found=0;
        break;
    case 8:
        cout<<"Thank you for using our media player!";
        flag=1;
        break;
        }
    }
}





