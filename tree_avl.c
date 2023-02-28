#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


struct node { // структура для представления узлов дерева
    int field;
    unsigned char height;
    node* left;
    node* right;
    node(int k) { field = k; left = right = 0; height = 1; }
};

void treeprint_infix(node *p) {
  if (p!=NULL) {                     //Пока не встретится пустой узел
    treeprint_infix(p->left);        //Рекурсивная функция для левого поддерева
    printf("%d ", p->field);         //Отображаем корень дерева
    treeprint_infix(p->right);       //Рекурсивная функция для правого поддерева
  }
}
void treeprint_prefix(node *p) {
  if (p!=NULL) {                     //Пока не встретится пустой узел
    printf("%d ", p->field);             //Отображаем корень дерева
    treeprint_prefix(p->left);       //Рекурсивная функция для левого поддерева
    treeprint_prefix(p->right);      //Рекурсивная функция для правого поддерева
  }
}

unsigned char height(node* p){ // возвращение высоты заданного узла
    return p ? (p->height) : 0;
}

int bfactor(node* p){ // вычисление balance factor заданного узла
    return height(p->right) - height(p->left);
}

void fixheight(node* p){ // вычисление высоты заданного узла
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr ? hl : hr) + 1;
}

node* rotateright(node* p) { // правый поворот вокруг p
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q){  // левый поворот вокруг q
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance_tree(node* p){ // балансировка узла p
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

node* insert(node* p, int k){ // вставка ключа k в дерево с корнем p
    if( !p ) return new node(k);
    if( k < (p->field) )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    return balance_tree(p);
}

node* findmin(node* p){ // поиск узла с минимальным ключом в дереве p 
    return ((p->left) ? findmin(p->left) : p);
}

node* remove_min(node* p) { // удаление узла с минимальным ключом из дерева p
    if( (p->left)==0 )
        return (p->right);
    p->left = remove_min(p->left);
    return balance_tree(p);
}

node* findnode(node *p, int x) { // поиск узла с данным ключом x в дереве p 
    if (p == NULL) return NULL;
    if ( x == (p->field)) return (p);
    if ( x  < (p->left->field ))  findnode(p->left,  x);
    if ( x  > (p->right->field))  findnode(p->right, x);
}

node* remove(node* p, int k) { // !!! УДАЛЕНИЕ УЗЛА с ключом k из дерева p !!!!!
    if( !p ) return 0;
    if( k < (p->field) )
        p->left =  remove(p->left,  k);
    else if( k > p->field )
        p->right = remove(p->right, k);  
    else //  k == p->field 
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if( !r ) return q;
        node* min = findmin(r);
        min->right = remove_min(r);
        min->left = q;
        return balance_tree(min);
    }
    return balance_tree(p);
}

void Random_test() {
    printf("Random data\n");
    int arr[] = {1000, 5000, 20000, 100000, 200000, 500000, 750000, 1000000, 5000000, 10000000}; //размер дерева 
    srand(time(NULL));
    for (int j = 0 ; j < 10; j++) {
        int n = arr[j];
        unsigned int start_time =  clock(); // начальное время
        
        struct node* p0 = NULL;
        for (int i = 0 ; i < n; i++) {
            int elem = rand() % 100;
            struct node* p1 = insert(p0, elem);
            p0 = p1;
        }
        unsigned int end_time = clock(); // конечное время
        unsigned int search_time = end_time - start_time; // искомое время
        printf("n = %d time = %d ms \n", n, search_time);
    }
}

void Sorted_test() {
    printf("\nSorted data\n");
    int arr[] = {1000, 5000, 20000, 100000, 200000, 500000, 750000, 1000000, 5000000, 10000000}; //размер дерева 
    for (int j = 0 ; j < 10; j++) {
        int n = arr[j];
        unsigned int start_time =  clock(); // начальное время
        struct node* p0 = NULL;
        for (int i = 0 ; i < n; i++) {
            int elem = i * 10;
            struct node* p1 = insert(p0, elem);
            p0 = p1;
        }
        
        unsigned int end_time = clock(); // конечное время
        unsigned int search_time = end_time - start_time; // искомое время
        printf("n = %d time = %d ms \n", n, search_time);
    }
}


void Quick_test() {
    printf("Spicial data\n");
    int arr[] = {1000, 5000, 20000, 100000, 200000, 500000, 750000, 1000000, 5000000, 10000000}; //размер дерева 
    for (int j = 0 ; j < 10; j++) {
        int n = arr[j];
        unsigned int start_time =  clock(); // начальное время
        struct node* p0 = NULL;
        for (int i = 0 ; i < n; i++) {
            int elem = 100 + pow(-1, i) * i;
            struct node* p1 = insert(p0, elem);
            p0 = p1;
        }
        
        unsigned int end_time = clock(); // конечное время
        unsigned int search_time = end_time - start_time; // искомое время
        printf("n = %d time = %d ms \n", n, search_time);
    }
}
int main() {
    Sorted_test();
    Random_test();
    Quick_test();  
}


