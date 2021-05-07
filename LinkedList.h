#ifndef LINKED_H
#define LINKED_H

#include <iostream>
//implimentation of a genric double sided liked list 
template<class T>
class DoublyLinkedList
{
    class Node
    {
        public:
            T data;
            Node* next;
            Node* prev;
            Node(T val): data(val), next(nullptr), prev(nullptr) {}
    };
    public:
        Node *head;//the first node of the list
        int size;//the number of objects in the list

  public:
      DoublyLinkedList(): head(nullptr),size(0){}
      class ALREADY_EXIST{};
      class NOT_EXIST{};
     ~DoublyLinkedList()
      {
          Node *tmp = nullptr;
          while (head)
          {
              tmp = head;
              head = head->next;
              delete tmp;
          }
          head = nullptr;
      }
    //inseret a new node if its not already existing, inseration occurs in the head of the list therefore the complexity is of O(1)
      void insert(T val)
      {
          if(findVal(val)!=nullptr)
          {
              throw (ALREADY_EXIST());
          }
          Node *node = new Node(val);
          if (head == nullptr)
          {
              head = node;
          }
          else
          {
              node->next = head;
              head = node;
              node->next->prev = node;
          }
          size++;
      }

 //remove a node if its existing, removal demends going through all of the list therefore the complexity is of O(n)
     void deleteVal(T val)
     {
          Node* find = findVal(val);
          if(find==nullptr)
            throw(NOT_EXIST());
          Node *tmp = head;
          if(tmp == find)
          {
              head = tmp->next;
          }
          else
          {
              while(find != nullptr)
              {
                  if(tmp->next == find)
                  {
                      tmp->next = find->next;
                      if(find->next ==nullptr)
                      {
                          size--;
                          delete find;
                          return;
                      }
                      find->next->prev = tmp;
                      delete find;
                      size--;
                      return;
                  }
                  tmp = tmp->next;
              }
          }
      }


     friend std::ostream & operator<<(std::ostream & os, const DoublyLinkedList<T> & dll){
      dll.display(os);
      return os;
     }

         Node *findVal(T n) //returns node of the given value
         {    
              Node *node = head;
              while(node != nullptr)
              {
                    if(node->data == n)
                          return node;

                    node = node->next;
              }
              return nullptr;
          }

       void display(std::ostream& out = std::cout) const
       {
            Node *node = head;
            while(node != nullptr)
            {
                out << node->data << " ";
                node = node->next;
            }
        } 
};

#endif