//
// Created by rodri on 11/7/2019.
//
#ifndef AVL_AVL_H
#define AVL_AVL_H
#define NODE Node<T>
#include <queue>
#include <iostream>

using namespace std;
template <class T>
struct Node{
    NODE* right=nullptr;
    NODE* left=nullptr;
    NODE* parent=nullptr;
    int height;
    T value;
    Node(const T& mvalue, NODE* mparent){
        value=mvalue;
        parent=mparent;
        height=1;
    }
    explicit Node(const T& mvalue){
        value=mvalue;
        height=1;
    }

    ~Node(){
        cout<<"Deleted node with value: "<<value<<endl;
    }
};


template <class T>
class AVLTree{
    NODE* root=nullptr;

public:
    AVLTree(){}
    explicit AVLTree(const T& value){
        root=new NODE(value);
    }

    NODE* get_root(){
        return root;
    }

    void postorder(NODE* node){
        if(node==nullptr){
            return;
        }
        print_postorder(node->left);
        print_postorder(node->right);
        cout<<node->data<<" ";
    }

    void inorder(NODE* node){
        if(node==nullptr){
            return;
        }
        print_inorder(node->left);
        cout<<node->key<<" ";
        print_inorder(node->right);
    }



    void preorder(NODE* node){
        if(node==nullptr){
            return;
        }
        cout<<node->data<<" ";
        print_preorder(node->left);
        print_preorder(node->right);
    }

    void levelorder(NODE* _root){
        if(_root==nullptr){
            return;
        }
        queue<NODE*> q;
        q.push(_root);
        while(!q.empty()){
            int nodos=q.size();
            while(nodos > 0){
                NODE* node=q.front();
                cout<<node->value<<" ";
                q.pop();
                if(node->left !=nullptr){
                    q.push(node->left);
                }
                if(node->right !=nullptr){
                    q.push(node->right);
                }
                nodos--;
            }
            cout<<endl;
        }
    }

    NODE* parent(const T& value){
        NODE* curr=root;
        NODE* parent=nullptr;
        while(curr){
            parent=curr;
            if(value > curr->value){
                curr=curr->right;
            }
            else{
                curr=curr->left;
            }
        }
        return parent;
    }

    NODE* right_rotate(NODE* mnode){
        NODE* mroot=mnode;
        NODE* child=mnode->left;
        mroot->left=child->right;
        if(child->right){
            child->right->parent=mroot;
        }
        child->right=mroot;
        if(mroot->parent){
            if(mroot->parent->right==mroot){
                mroot->parent->right=child;
            }
            else{
                mroot->parent->left=child;
            }
            mroot->parent=child;
        }
        child->parent=mroot->parent;
        if(mnode==root){
            root=child;
        }
        mroot->height=get_height(mroot);
        child->height=get_height(child);
    }


    NODE* left_rotate(NODE* mnode){
        NODE* mroot=mnode;
        NODE* mchild=mnode->right;
        mroot->right=mchild->left;
        if(mchild->left){
            mchild->left->parent=mroot;
        }
        mchild->left=mroot;
        if(mroot->parent){
            if(mroot->parent->right==mroot){
                mroot->parent->right=mchild;
            }
            else{
                mroot->parent->left=mchild;
            }
            mroot->parent=mchild;
        }

        mchild->parent=mroot->parent;
        if(mnode==root){
            root=mchild;
        }
        mroot->height=get_height(mroot);
        mchild->height=get_height(mchild);
}

    void insert(const T& mnode){
        if(root==nullptr){
            root=new NODE(mnode);
            return;
        }
        else{
            aux_insert(root, mnode);
        }
    }


    void aux_insert(Node<T>* mnode, const T& mvalue){
        if(mnode->value < mvalue){
            if(mnode->right){
                aux_insert(mnode->right, mvalue);
            } else{
                mnode->right=new NODE(mvalue, mnode);
            }
        } else if(mnode->value > mvalue){
            if(mnode->left){
                aux_insert(mnode->left, mvalue);
            }
            else{
                mnode->left=new NODE(mvalue, mnode);
            }
        } else{
            return;
        }

        mnode->height=height_difference_of_node(mnode);

        int height_dif=height_difference_of_node(mnode);

        if(height_dif < -1 && mvalue < mnode->left->value){
            right_rotate(mnode);
        } else if(height_dif > 1 && mvalue > mnode->right->value){
            left_rotate(mnode);
        } else if(height_dif > 1 && mvalue < mnode->right->value){
            right_rotate(mnode->right);
            left_rotate(mnode);
        } else if(height_dif < -1 && mvalue > mnode->left->value){
            left_rotate(mnode->left);
            right_rotate(mnode);
        }
    }

    int get_height(NODE* node){
        if(node==nullptr){
            return 0;
        }
        else{
            int iz=get_height(node->left);
            int der=get_height(node->right);
            if(iz > der){
                return iz + 1;
            }
            else{
                return der + 1;
            }
        }
    }

    int height_difference_of_node(NODE* mnode){
        return int(get_height(mnode->right)) - int(get_height(mnode->left));
    }

    void clear(NODE* mroot){
        if(mroot==nullptr)
            return;
        clear(mroot->left);
        clear(mroot->right);
        delete mroot;
    }

    ~AVLTree(){
        clear(root);
        cout<<"AVLTree deleted "<<endl;
    }
};

#endif //AVL_AVL_H
