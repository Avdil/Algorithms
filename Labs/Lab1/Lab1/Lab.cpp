#include<iostream>
#include<limits.h>
using namespace std;
const int n = 6;
double mat_o;
struct Tree {
	int key;
	Tree *parent;
	Tree *left;
	Tree *right;
	bool leaf;
	double pq;
	int d;
};
void Insert(Tree *&T, int v, bool l, double *p, double *q);
void Print(Tree *T, double *p, double *q);
//void init(double p[n], double q[n], double **e, double **w, int **root);
void optimal_BST(double *p, double *q, int n, double **e, double **w, int **root);
void print_arrays(double **e, double **w, int **root);
void build(Tree *&T, int **root, int i, int j, double *p, double *q);

void main() {
	Tree *T = NULL;
	double *p = new double[n + 1]{ 0, 0.15, 0.10, 0.05, 0.10, 0.20 };
	double *q = new double[n + 1]{ 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 };
	double **e = new double*[n + 1]; // n+1 строка в массиве
	for (int i = 0; i < n + 1; i++) {
		e[i] = new double[n];
	}
	double **w = new double*[n + 1]; // n+1 строка в массиве
	for (int i = 0; i < n + 1; i++) {
		w[i] = new double[n];
	}
	int **root = new int*[n]; 
	for (int i = 0; i < n; i++) {
		root[i] = new int[n];
	}
	//init(p, q, e, w, root);
	optimal_BST(p, q, n, e, w, root);
	print_arrays(e, w, root);
	build(T, root, 1, n - 1, p, q);
	Print(T, p, q);
	cout << "\nMathematical expectation = " << mat_o << endl;
	cin.get();
	cin.get();
}


void Insert(Tree *&T, int v, bool l, double *p, double *q) {
	Tree *x = T, *y = NULL;
	Tree *z = new Tree;
	z->left = NULL; z->right = NULL; z->key = v; z->leaf = l; z->d = 0;
	if (z->leaf == false)
		z->pq = p[v];
	if (z->leaf == true)
		z->pq = q[v];

	while (x != NULL) {
		y = x;
		if (v <= x->key)
			x = x->left;
		else
			x = x->right;
	}
	if (y != NULL){
		z->parent = y;
		z->d = y->d + 1;
	}
	if (y == NULL)
		T = z;
	else {
		if (z->key <= y->key)
			y->left = z;
		else
			y->right = z;
	}

}
void Print(Tree *T, double *p, double *q) {
	Tree *x = T;
	if (x != NULL) {
		Print(x->left, p, q);
		if (x->leaf)
			cout << "d";
		else
			cout << "k";
		cout << x->key << "\t";
		if (x->leaf)
			cout << q[x->key];
		else
			cout << p[x->key];
		cout << "\t" << x->d << "  ";
		if (x->leaf)
			cout << "leaf\n";
		else
			cout << "node\n";
		mat_o = mat_o + (x->d + 1) * T->pq;
		Print(x->right, p, q);
	}
}
//void init(double p[n], double q[n], double **e, double **w, int **root) {
//	cout << "Enter mas p: ";
//	for (int i = 1; i <= n; i++) {
//		cin >> p[i];
//	}
//	cout << "Enter mas q: ";
//	for (int i = 0; i <= n; i++) {
//		cin >> q[i];
//	}
//
//	e = new double*[n + 1]; // n+1 строка в массиве
//	for (int i = 0; i < n + 1; i++) {
//		e[i] = new double[n];
//	}
//	w = new double*[n + 1]; // n+1 строка в массиве
//	for (int i = 0; i < n + 1; i++) {
//		w[i] = new double[n];
//	}
//	root = new int*[n]; // n+1 строка в массиве
//	for (int i = 0; i < n; i++) {
//		root[i] = new int[n];
//	}
//}
void optimal_BST(double *p, double *q, int n, double **e, double **w, int **root) {
	for (int i = 1; i < n + 1; i++) {
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (int l = 1; l < n; l++)
	{
		for (int i = 1; i < n - l + 1; i++) {
			int j = i + l - 1;
			e[i][j] = INT_MAX;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int r = i; r <= j; r++) {
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j]){
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
}
void print_arrays(double **e, double **w, int **root) {
	cout << "\nTable E\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i - 1; j++)
			cout << " \t"; // сдвиг для вывода аналогично рисунку
		for (int j = i - 1; j < n; j++)
			cout << e[i][j] << '\t';
		cout << endl;
	}
	cout << "\nTable W\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i - 1; j++)
			cout << " \t"; // сдвиг для вывода аналогично рисунку
		for (int j = i - 1; j < n; j++)
			cout << w[i][j] << '\t';
		cout << endl;
	}
	cout << "\nTable Root\n";
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++)
			cout << " \t"; // сдвиг для вывода аналогично рисунку
		for (int j = i; j < n; j++)
			cout << root[i][j] << '\t';
		cout << endl;
	}
}
void build(Tree *&T, int **root, int i, int j, double *p, double *q) {
	if (i <= j) {
		int k = root[i][j];
		Insert(T, k, 0, p, q); //0 для leaf
		build(T, root, i, k - 1, p, q);
		build(T, root, k + 1, j, p, q);
	}
	else
		Insert(T, j, 1, p, q);
}
