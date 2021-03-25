#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	
	vector<int> arr(n);
	for (int& u: arr) cin >> u;
	sort(arr.begin(), arr.end());

	for (int& u: arr) cout << u;
}
