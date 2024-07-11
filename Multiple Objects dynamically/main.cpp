#include <iostream>
using namespace std;

// Class A with a constructor that prints a message when an object is created
class A {
public:
    A() {
        cout << "# Object existed" << endl;
    }
};

// Function declaration:
// 1. Function name: func
// 2. Parameters: 
//    - array: an array of objects of class A
//    - size: an integer representing the size of the first array
//    - newsize: a reference to an integer representing the size of the second array
// 3. Returns: an object of class A
A func(A array[], int size, int &newsize) {
    // Create a new array of objects of class A with the size newsize
    A newarray[newsize];
    
    // Check if the sizes of the two arrays are equal
    if(size == newsize) {
        cout << "They were Equal ";
        // Return an object from the new array
        return newarray[newsize];
    } else {
        // If sizes are not equal, set newsize to 0
        newsize = 0;
        cout << "They were not Equal ";
    }
    
    // Return an object from the original array
    return array[size];
}

int main() {
    // Initialize integer variables b and c
    int b = 0, c;
    
    // Create an array of objects of class A with size b
    A a[b];
    
    // Prompt user to enter the size of the first array
    cout << "Enter the first array object size: " << endl;
    cin >> b;
    
    // Prompt user to enter the size of the second array
    cout << "Enter the second array object size: " << endl;
    cin >> c;
    
    // Call the func function with the array a, size b, and size c
    func(a, b, c);
    
    // Return 0 to indicate successful execution
    return 0;
}

