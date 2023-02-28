#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
	struct node* left;
	char* field;
	struct node* right;
	int h;
	
} tree;



int height_tr(node* p){
    return p ? (p->h) : 0;
}

int height(tree* t) {
	if (!t) return 0;
	int hl = height_tr(t->right);
    int hr = height_tr(t->left);
    t->h =  (hl>hr ? hl : hr) + 1;
	return t->h;
}

tree* current_tree(tree* left, char* x, tree* right) {
	tree* n = (tree*) calloc(1, sizeof(tree));
	int hl = height_tr(left);
    int hr = height_tr(right);
	*n = (tree){left, x, right, (hl>hr ? hl : hr) + 1};
	return n;
}

tree* balance(tree* left, char* x, tree* right) {
	tree* n;
	int b = height_tr(right) - height_tr(left);
	if ( b > 1) {
		if ( height_tr(right->right) > height_tr(right->left) ) {
			n = current_tree(current_tree(left, x, right->left), right->field, right->right);
		} else {
			tree* rl = right->left;
			n = current_tree(current_tree(left, x, rl->left), rl->field, current_tree(rl->right, right->field, right->right));
			free(rl);
		}
		free(right);
		return n;
	} else if ( b < -1) {
		if ( height_tr(left->left) > height_tr(left->right) )
			n = current_tree(left->left, left->field, current_tree(left->right, x, right));
		else {
			tree* lr = left->right;
			n = current_tree(current_tree(left->left, left->field, lr->left), lr->field, current_tree(lr->right, x, right));
			free(lr);
		}
		free(left);
		return n;
	}
	return current_tree(left, x, right);
}


tree* insert(tree* t, char* field) {
	if ( ! t ) {
		return balance(NULL, strdup(field), NULL);
	} else {
		tree* left = t->left, *right = t->right;
		char* x = t->field;
		free(t);
		if ( strcmp(field, x) <= 0 ) return balance(insert(left, field), x, right);
		else return balance(left, x, insert(right, field));
	}
}


void remove(tree* t) {
	if ( t ) {
		tree*left = t->left, *right = t->right;
		free(t->field);
		free(t);
		remove(left);
		remove(right);
	}
}


int prefix_search(tree* t, const char* prefix) {
	int e = 1; 
	if (t) {

		int res = strncmp (prefix, t->field, strlen (prefix));

		if (res <= 0) { if (prefix_search (t->left, prefix) == 0) e = 0;}
		if (res == 0) { printf ("%s", (t->field)); e = 1; return 1;}
		if (res >= 0) { if (prefix_search (t->right, prefix)== 0) e = 0;}
	    return e;
	}
	else return 0;
}


int main() {

	char a[1000];
	int i = 0;
	tree* tree = NULL;
	printf("enter tree elements: (end the input with CTRL + Z) \n");
	while (scanf("%s", a) == 1) {
		tree = insert(tree, a);
		i++;
	}
	printf ("\n");
	printf ("enter the search prefix: ");
	scanf ("%s", a);
	printf("keys with the beginning on the entered prefix: \n");
	if (prefix_search (tree, a) == 0) printf("no relevant elements\n");
	remove(tree);
}