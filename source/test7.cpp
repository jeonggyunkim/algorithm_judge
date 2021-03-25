#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> SORT(vector<int> arr, int n) {
	if (n == 0) return arr;
	for (int i = 1; i < arr.size(); ++i) {
		if (arr[i - 1] > arr[i]) swap(arr[i - 1], arr[i]);
	}
	arr = SORT(arr, n - 1);
	return arr;
}

int main() {
	int n;
	cin >> n;
	
	vector<int> arr(n);
	for (int& u: arr) cin >> u;

	vector<int> ans = SORT(arr, n);
	for (int& u: ans) cout << u << ' ';
}
