#include<iostream>
#include<vector>
#include<cmath>
#define pi 3.141592653589793238462643383279502884197169399375105820974944592307816406286
using namespace std;

int howLong(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

int th(double x, double y) {
	return atan2(y-300,x-300)*(180/pi) + 90;
}

bool checkPoint(int x, int y) {
	if (howLong(x, y, 300, 300) == 300)	return true;
	if (howLong(x, y, 300, 300) == 150)	return true;
	return false;
}

vector<int> clean(vector<int> x, vector<int> y, int n) {
	vector<int> nx, ny, answer;
	
	for (int i = 0;i < n;i++) {
		answer.push_back(x[i]);
		answer.push_back(y[i]);
	}

	for (int i = 0;i < n-1;i++) {
		for (int k = i+1;k < n;k++) {
			int* x1 = &answer[i * 2], * y1 = &answer[i * 2 + 1];
			int* x2 = &answer[k * 2], * y2 = &answer[k * 2 + 1];
			if (th(*x1, *y1)%360 < th(*x2, *y2)%360) {
				swap(*x1, *x2);
				swap(*y1, *y2);
			}	
		}
	}

	return answer;
}

vector<int> solution(vector<int> x, vector<int> y,int n) {
	vector<int> nx,ny,answer;
	answer=clean(x, y, n);

	for (int i = 0;i < n;i++) {
		int *xx=&answer[i * 2], *yy=&answer[i * 2 + 1];
		float r,l= howLong(*xx, *yy, 300, 300);
		if (howLong(*xx, *yy, 300, 300) > 150+75)	r = 300;
		else r = 150;
		*xx = (int)(r* (*xx-300)/l+300);
		*yy = (int)(r* (*yy-300)/l+300);
	}
	
	return answer;
}

int main() {
	vector<int> x, y, answer;
	int n=0,tempx,tempy;
	while (cin >> tempx >> tempy) {
		x.push_back(tempx);
		y.push_back(tempy);
		n++;
	}

	answer = solution(x, y, n);
	cout << "Outer: ";
	for (int i = 0;i < answer.size() / 2;i++) {
		int* xx = &answer[i * 2], * yy = &answer[i * 2 + 1];
		if (howLong(*xx, *yy, 300, 300) > 150 + 75) {
			cout << *xx << "," << *yy <<' ';
		}
	}
	cout <<endl<< "Inner: ";
	for (int i = 0;i < answer.size() / 2;i++) {
		int* xx = &answer[i * 2], * yy = &answer[i * 2 + 1];
		if (howLong(*xx, *yy, 300, 300) <= 150 + 75)
			cout << *xx << "," << *yy << ' ';
	}
	cout << endl;
    return 0;
}