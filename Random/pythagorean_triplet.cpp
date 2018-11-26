#include <algorithm>
#include <iostream>

using namespace std;

bool
hasPythagoreanTriplet( int arr, size_t len ) {
}

bool
hasPythagoreanTriplet( int arr[], size_t len ) {
    for( size_t i = 0; i < len; ++i ) { // O(n)
        arr[i] *= arr[i];
    }

    sort( arr, arr + len ); // O(nlogn)

    for( size_t i = len-1; i >= 2; --i ) {
        size_t l = 0;
        size_t h = i - 1;

        while( l < h ) {
            if( arr[l] + arr[h] == arr[i] ) {
                return true;
            }

            if( arr[l] + arr[h] < arr[i] ) {
                l++;
            } else {
                h--;
            }
        }
    }
    return false;
}

int
main()
{
    int arr[] = {3, 1, 4, 6, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);


    if( hasPythagoreanTriplet( arr, arr_size ) ) {
        cout << "Yes! Pythagorean triplet.";
    } else {
        cout << "No!";
    }
    cout << endl;
}
