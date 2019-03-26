#include <iostream>
using namespace std;

long long factorial(int n)
{
    //base case
    if (n == 0)
        return 1;

    else
        return n * factorial(n - 1);
}

bool search(int k, int V[], int start, int end) {
    if (end < start) return false;
    
    int mid = start + (end-start) / 2;

    if (V[mid] == k) return true;

    else if (k > V[mid])
        return search(k, V, mid + 1, end);
    
    return search(k, V, start, mid - 1);
}

    long long fibbonacci(int month) {
        if(month == 0 || month == 1) return month;

        return fibbonacci(month - 1) + fibbonacci(month - 2);
    }

int main()
{
    int arr [] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << endl << factorial(4);

    search(22, arr, 0, 9) ? cout << endl
                                << "found"
                         : cout << endl
                                << "not found";
    
    cout << endl << "rabbits in pair: " << fibbonacci(3) << endl;

                                
    return 0;
}


