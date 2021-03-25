#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	
	vector<int> arr(n);
	for (int& u: arr) cin >> u;

	for (int i = 1; i < n; ++i) {
		for (int j = i; j > 0; --j) {
			if (arr[j] < arr[j - 1]) swap(arr[j - 1], arr[j]);
			else break;
		}
	}

	for (int& u: arr) cout << u << ' ';
}
