#include <bits/stdc++.h>
using namespace std;

class item{
    int key,value;
    public :
        item(int key, int value){
            this->key=key;
            this->value=value;
        }
        void print_data(){
            cout<<"key is "<<key<<" and value is "<<value;
        }
};
typedef struct Node{
    int key;
    int value;
    struct Node* next;
} Node;
class node{
    public:
        Node* create_node(int key, int value){
            Node* temp = new Node();
            temp->next=NULL;
            temp->key=key;
            temp->value=value;
            return temp;
        }
        void delete_node(Node **temp){
            free(*temp);
        }
};
class hash_map{
    vector<Node*>map_list;
    vector<item>items;
    int total_key;
    node tmp;
    int get_hash(int key){
        return key%total_key;
    }
    void key_exist(Node** temp, int key){
        Node* tmp=*temp;
        while(tmp->next!=NULL && tmp->key!=key){
            tmp=tmp->next;
        }
        *temp=tmp;
    }
    public:
        hash_map(int key){
            total_key=key;
            for(int i=0;i<key;i++){
                Node* temp=tmp.create_node(0,0);
                map_list.push_back(temp);
            }
        }
        void insert_key(int key, int value){
            items.push_back(item(key,value));
            int hash_key=get_hash(key);
            //cout<<hash_key<<" ";
            Node* temp=map_list[hash_key];
           // cout<<temp<<" ";
            key_exist(&temp, key);
            if(temp->key!=key){
                Node* new_node=tmp.create_node(key, value);
                new_node->next=temp->next;
                temp->next=new_node;
            }
            else{
                temp->value=value;
            }
        }
        void print_push_key_value(){
            for(int i=0;i<items.size();i++){
                items[i].print_data();
                cout<<endl;
            }
        }
        
        int get_value(int key){
            int hash_key=get_hash(key);
            Node* temp=map_list[hash_key];
            key_exist(&temp, key);
            if(temp->key!=key){
                return -1;
            }
            else{
                return temp->value;
            }
        }
        
        void delete_key(int key){
            int hash_key=get_hash(key);
            Node* temp=map_list[hash_key];
            while(temp->next!=NULL && temp->next->next!=NULL && temp->next->key!=key){
                temp=temp->next;
            }
            if(temp->next==NULL){
                return ;
            }
            else if(temp->next->key==key){
                Node* node_to_delete=temp->next;
                temp->next=node_to_delete->next;
                node_to_delete->next=NULL;
                tmp.delete_node(&(node_to_delete));
            }
        }
};
int main() {
    // your code goes here
    hash_map hash_map_obj(10);
    hash_map_obj.insert_key(5, 5);
    hash_map_obj.insert_key(3, 6);
    hash_map_obj.insert_key(13, 13);
    cout<<hash_map_obj.get_value(13)<<endl;
    hash_map_obj.insert_key(23, 23);
    hash_map_obj.insert_key(13, 113);
    cout<<hash_map_obj.get_value(13)<<endl;
    hash_map_obj.delete_key(7);
    hash_map_obj.delete_key(13);
    cout<<hash_map_obj.get_value(13)<<endl;
    hash_map_obj.print_push_key_value();
    return 0;
}
