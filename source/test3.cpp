#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	
	vector<int> arr(n);
	for (int& u: arr) cin >> u;
	sort(arr.begin(), arr.end());

	for (int& u: arr) cout << u << ' ';
}
