#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "matplotlibcpp.h"

namespace plt=matplotlibcpp;
using namespace std;

//Case 1: a>b^k -> T(n)=8T(n/2)+ n^2-> O(n^3)
long long case1(int n){
    if (n<=1) return 1;
    return 8*case1(n/2)+n *n;
}

//Case 2: a=b^k -> T(n)=4T (n/2) + n^2 log n -> O(n^2 log^2 n)
long long case2(int n){
    if (n<=1) return 1;
    return 4* case2(n/2)+n*n*log2(n);
} 

//Case 3a: a<b^k -> T(n)=T (n/2)+ n -> O(n)
long long case3a(int n){
    if (n<=1) return 1;
    return case3b(n/2)+1;
}

// Case 3b: a<b^k -> T(n) = T(n/2)+1 -> O(log n)
long long case3b(int n){
    if (n<=1) return 1;
    return case3b(n/2)+1;
}

int main(){
    vector<int> n_values;
    vector<long long> work_case1, work_case2, work_case3a, work_case3b;

    for (int n=2; n<=256; n*=2){
        n_values.push_back(n);
        work_case1.push_back(case1(n));
        work_case2.push_back(case2(n));
        work_case3a.push_back(case3a(n));
        work_case3b.push_back(case3b(n));
    }

    plt::figure_size(1000, 600);
    plt::plot(n_values, work_case1, "r-", {{"label", "Case 1: O(n^3)"}});
    plt::plot(n_values, work_case2, "b--", {{"label", "Case 2: O(n^2 log^2n)"}});
    plt::plot(n_values, work_case3a, "g-", {{"label", "Case 3a: O(n)"}});
    plt::plot(n_values, work_case3b, "k:", {{"label", "Case 3b: O(log n)"}});

    plt::title("Master Theorem Cases - Recurrence Work Comparison");
    plt::xlabel("n");
    plt::ylabel("Work (recurrence output)");
    plt::legend();
    plt::grid(true);
    plt::save("master_theorem_cases.png");
    plt::show();

    return 0;
}