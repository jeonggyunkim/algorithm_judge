#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
	FILE* f = fopen(argv[1], "rt");

	int n;
	fscanf(f, "%d", &n);

	fclose(f);

	FILE* f1 = fopen(argv[2], "rt");
	FILE* f2 = fopen(argv[2], "rt");

	int t1, t2;
	for (int i = 0; i < n; ++i) {
		fscanf(f1, "%d", &t1);
		fscanf(f2, "%d", &t2);
		if (t1 != t2) {
			return -1;
		}
	}
	fclose(f1);
	fclose(f2);
}
