#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct tnode {
  int field;           // поле данных
  struct tnode *left;  // левый потомок
  struct tnode *right; // правый потомок
};


void treeprint_prefix(tnode *tree) {
  if (tree!=NULL) {                     //Пока не встретится пустой узел
    printf("%d ", tree->field);             //Отображаем корень дерева
    treeprint_prefix(tree->left);       //Рекурсивная функция для левого поддерева
    treeprint_prefix(tree->right);      //Рекурсивная функция для правого поддерева
  }
}

void treeprint_infix(tnode *tree) {
  if (tree!=NULL) {                     //Пока не встретится пустой узел
    treeprint_infix(tree->left);        //Рекурсивная функция для левого поддерева
    printf("%d ", tree->field);         //Отображаем корень дерева
    treeprint_infix(tree->right);       //Рекурсивная функция для правого поддерева
  }
}

void treeprint_postfix(tnode *tree) {
  if (tree!=NULL) {                    //Пока не встретится пустой узел
    treeprint_postfix(tree->left);     //Рекурсивная функция для левого поддерева
    treeprint_postfix(tree->right);    //Рекурсивная функция для правого поддерева
    printf("%d ", tree->field);           //Отображаем корень дерева
  }
}


struct tnode* addnode(int x, tnode *tree) {
  if (tree == NULL) {                 // Если дерева нет, то формируем корень
    tree = new tnode;                  // память под узел
    tree->field = x;                  // поле данных
    tree->left  = NULL;
    tree->right = NULL;               // ветви инициализируем пустотой
  } else if (x < tree->field)         // условие добавление левого потомка
    tree->left = addnode(x,tree->left);
  else                                // условие добавление правого потомка
    tree->right = addnode(x, tree->right);
  return(tree);
}

struct tnode* findnode(int x, tnode *tree) {
    if (tree == NULL) return NULL;
    if ( x == (tree->field)) return (tree);
    if ( x  < (tree->left->field))  findnode(x, tree->left);
    if ( x  > (tree->right->field)) findnode(x, tree->right);
}


void freemem(tnode *tree) {
  if(tree!=NULL) {
    freemem(tree->left);
    freemem(tree->right);
    delete tree;
  }
}


void Random_test() {
    printf("Random data\n");
    int arr[] = {1000, 5000, 20000, 100000, 200000, 500000, 750000, 1000000, 5000000, 10000000}; //размер дерева 
    srand(time(NULL));
    for (int j = 0 ; j < 10; j++) {      
      int n = arr[j];
      unsigned int start_time =  clock(); // начальное время
      
      struct tnode* p0 = addnode(10, NULL);
      for (int i = 0 ; i < n; i++) {
          int elem = rand() % 100;
          struct tnode* p1 = addnode(elem, p0);
          p0 = p1;
      }    
      unsigned int end_time = clock(); // конечное время
      unsigned int search_time = end_time - start_time; // искомое время
      printf("n = %d time = %d ms\n", n, search_time);
    }
}

void Sorted_test() {
    printf("\nSorted data\n");
    int arr[] = {1000, 5000, 20000, 100000, 200000, 500000, 750000, 1000000, 5000000, 10000000}; //размер дерева 
    for (int j = 0 ; j < 10; j++) {      
      int n = arr[j];
      unsigned int start_time =  clock(); // начальное время
      
      struct tnode* p0 = addnode(10, NULL);
      for (int i = 0 ; i < n; i++) {
          int elem = i * 10;
          struct tnode* p1 = addnode(elem, p0);
          p0 = p1;
      }    
      unsigned int end_time = clock(); // конечное время
      unsigned int search_time = end_time - start_time; // искомое время
      printf("n = %d time = %d ms\n", n, search_time);
    }
}

int main() {
    //Random_test();  
    Sorted_test();
}
