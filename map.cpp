#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;
double p1(int frame, int empty, int tags) {
    return pow((1-(double)empty/frame),tags);
}

double fat(int f) {
    double r = 1;
    while (f>0) {
        r *= f--;
    }
    return r;
}

double binomial(int n, int s) {
    return fat(n)/(fat(s)*fat(n-s));
}

double p2(int frame, int empty, int success, int tags) {
    // cout << "bi " << binomial(tags, success) << endl;
    double res = binomial(tags, success)*(pow(frame - empty - success,tags - success)/pow(frame-empty, tags))*fat(success);
    // cout << res << endl;
    // cout << "p2" << endl;
    return res;
}

double p3(int frame, int empty, int success, int colisao, int tags) {
    double res = 0;
    for (int k = 0; k < colisao;k++) {
        for (int v = 0;v<colisao - k;v++) {
            res += pow(-1, k + v)*
            binomial(colisao, k)*
            binomial(colisao-k,v)*
            (fat(tags-success)/fat(tags-success-k))*
            (pow(colisao-k-v,tags-success-k)/pow(colisao,tags-success));
        }
    }
    // cout << res << endl;
    // cout << "p3" << endl;
    return res;
}


int main(int argc, char **argv)
{
    int frame = 10,
        empty = 9,
        success = 1,
        colisao = 0,
        tags = 2;
    while (true) {
        cin >> tags;
        double a1 = (fat(frame)/(fat(empty)*fat(success)*fat(colisao)));
        double a2 = p1(frame, empty, tags);
        double a3 = p2(frame, empty, success, tags);
        double a4 = p3(frame, empty, success, colisao, tags);
        cout << "#############################" << endl;
        cout << a1 << endl;
        cout << a2 << endl;
        cout << a3 << endl;
        cout << a4 << endl;
        cout << "#############################" << endl;
        cout << a1*a2*a3*a4 << endl;
    }
	return 0;
}