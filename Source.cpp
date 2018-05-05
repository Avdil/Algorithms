#include <iostream>
#include <limits.h>
#include <iomanip>

using namespace std;

double mo;
int n = 6;
struct tree {
	int key;
	bool leaf;
	int depth;
	double pq;
	tree *p;
	tree *left;
	tree *right;

};
void insert(tree *&T, int v, bool l, double*p1, double*q);
void print(tree *T, double* p1, double* q);
void optimal_BST(double *p1, double *q, int n, double **e, double ** w, int **root);
void printArrays(double **e, double **w, int **root);
void build(tree *&T, int **root, int i, int j, double *p1, double *q);
int main() {
	setlocale(0, "rus");
	cout << fixed << setprecision(2);
	double *p1 = new double[n + 1]{ 0, 0.15, 0.10, 0.05, 0.10, 0.20 };
	double *q = new double[n + 1]{ 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 };
	double **e = new double*[n + 1];
	for (int i = 0; i < n + 1; i++)
		e[i] = new double[n];
	double **w = new double*[n + 1];
	for (int i = 0; i < n + 1; i++)
		w[i] = new double[n];
	int **root = new int*[n];
	for (int i = 0; i < n + 1; i++)
		root[i] = new int[n];
	tree *T = nullptr;
	optimal_BST(p1, q, n, e, w, root);
	printArrays(e, w, root);
	build(T, root, 1, n - 1, p1, q);
	print(T, p1, q);
	cout << "\nmo = " << mo << endl;
}

void insert(tree *&T, int v, bool l, double*p1, double*q) {

	tree *y = nullptr;
	tree *x = T;
	tree *z = new tree;
	z->key = v;
	z->left = nullptr;
	z->right = nullptr;
	z->leaf = l;
	z->depth = 0;

	if (z->leaf)
		z->pq = q[v];
	else
		z->pq = p1[v];

	while (x != nullptr)
	{
		y = x;
		if (v < x->key)
			x = x->left;
		else
			x = x->right;
	}
	if (y != nullptr)
	{
		z->p = y;
		z->depth = y->depth + 1;
	}

	if (y == nullptr)
		T = z;
	else
	if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
}

void print(tree *T, double* p1, double* q) {

	if (T != nullptr) {
		print(T->left, p1, q);
		if (T->leaf)
			cout << 'd';
		else
			cout << 'k';
		cout << T->key << ", ";
		if (T->leaf)
			cout << q[T->key];
		else
			cout << p1[T->key];
		cout << ", " << T->depth << ", ";
		if (T->leaf)
			cout << "leaf\n";
		else
			cout << "node\n";
		mo = mo + (T->depth + 1) * T->pq;
		print(T->right, p1, q);
	}
}

void optimal_BST(double *p1, double *q, int n, double **e, double ** w, int **root) {
	for (int i = 1; i < n + 1; i++) {
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (int l = 0; l < n; l++) {
		for (int i = 1; i < n - l; i++) {
			int j = i + l;
			e[i][j] = INT_MAX;
			w[i][j] = w[i][j - 1] + p1[j] + q[j];
			for (int r = i; r <= j; r++) {
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j]) {
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
}

void build(tree *&T, int **root, int i, int j, double *p1, double *q) {
	if (i <= j) {
		int k = root[i][j];
		insert(T, k, 0, p1, q);
		build(T, root, i, k - 1, p1, q);
		build(T, root, k + 1, j, p1, q);
	}
	else
		insert(T, j, 1, p1, q);
}

void printArrays(double **e, double **w, int **root) {
	cout << "\nTable E\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i - 1; j++)
			cout << "    \t";
		for (int j = i - 1; j < n; j++)
			cout << e[i][j] << '\t';
		cout << endl;
	}
	cout << "\nTable W\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i - 1; j++)
			cout << "    \t";
		for (int j = i - 1; j < n; j++)
			cout << w[i][j] << '\t';
		cout << endl;
	}
	cout << "\nTable ROOT\n";
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++)
			cout << "    \t";
		for (int j = i; j < n; j++)
			cout << root[i][j] << '\t';
		cout << endl;
	}
}
