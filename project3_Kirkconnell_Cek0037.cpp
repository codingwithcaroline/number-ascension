// Name: Caroline Kirkconnell
// Auburn UserID: Cek0037
// Filename: project3_Kirkconnell_Cek0037.cpp
// Compile: VisualStudio
// I used StackOverflow to learn about streams, file I/O, and unit testing.
// Description: This program merges the numbers in two files and
// writes all the numbers into a third file. This program takes input
// from two different files and writes its output to a third file.
// Each input file contains a list of numbers of type int in sorted
// order from the smallest to the largest. After the program is run,
// the output file will contain all the numbers in the two input files
// in one longer list in sorted order from smallest to largest.

#include <fstream>
#include <iostream>
using namespace std;

// sets maximum size
const int MAX_SIZE = 100;

// reads file and displays numbers
int read_file(int input_array[], ifstream& instream) {
    int index = 0;

    instream >> input_array[index];
    while (!instream.eof()) {
        index++;
        instream >> input_array[index];
    }
    return index;
}

// merges files
void merge(int array[], int x, int y, int z) {
    int a, b, c;
    int n1 = y - x + 1;
    int n2 = z - y;

    int* X = new int[n1];
    int* Z = new int[n2];


    for (a = 0; a < n1; a++) {
        X[a] = array[x + a];
    }

    for (b = 0; b < n2; b++) {
        Z[b] = array[y + 1 + b];
    }

    a = 0;
    b = 0;
    c = x;
    while (a < n1 && b < n2) {
        if (X[a] <= Z[b]) {
            array[c] = X[a];
            a++;
        }
        else {
            array[c] = Z[b];
            b++;
        }
        c++;
    }

    while (a < n1) {
        array[c] = X[a];
        a++;
        c++;
    }

    while (b < n2) {
        array[c] = Z[b];
        b++;
        c++;
    }

    delete[] X;
    delete[] Z;
}

// sorts and displays numbers
void merge_sort(int array[], int x, int z)
{
    if (x < z) {
        int y = x + (z - x) / 2;

        merge_sort(array, x, y);
        merge_sort(array, y + 1, z);

        merge(array, x, y, z);
    }
}

// combines and sorts
int combine_and_sort(int array_1[], int array_1_size, int array_2[], int array_2_size, int output_array[]) {
    int output_array_size = array_1_size + array_2_size;

    for (int i = 0; i < array_1_size; i++) {
        output_array[i] = array_1[i];
    }
    for (int i = 0; i < array_2_size; i++) {
        output_array[i + array_1_size] = array_2[i];
    }
    merge_sort(output_array, 0, output_array_size - 1);

    return output_array_size;
}

// writes sorted list
void writefile(int output_array[], int output_array_size) {
    ofstream outstream;
    string output_filename;
    cout << "Enter the output file name: ";
    cin >> output_filename;

    outstream.open((char*)output_filename.c_str());
    for (int i = 0; i < output_array_size; i++) {
        outstream << output_array[i] << "\n";
    }
    outstream.close();

    cout << "*** Please check the new file - " << output_filename << " ***\n";
}

// main dialogue output
int main() {
    int array_1[MAX_SIZE];
    int array_1_size;
    int array_2[MAX_SIZE];
    int array_2_size;

    cout << endl << "*** Welcome to Caroline's sorting program ***\n";

    ifstream instream;
    string filename_1;
    bool valid_file_1 = false;
    while (!valid_file_1) {
        cout << "Enter the first input file name: ";
        cin >> filename_1;
        instream.open((char*)filename_1.c_str());
        valid_file_1 = instream.good();
        if (!valid_file_1) {
            cout << "Error: Invalid filename, please try again\n";
            cout << endl;
        }
    }

    array_1_size = read_file(array_1, instream);
    instream.close();

    cout << "The list of " << array_1_size << " numbers in file " << filename_1 << " is:\n";
    for (int i = 0; i < array_1_size; i++) {
        cout << array_1[i] << "\n";
    }
    cout << endl;

    string filename_2;
    bool valid_file_2 = false;
    while (!valid_file_2) {
        cout << "Enter the second input file name: ";
        cin >> filename_2;
        instream.open((char*)filename_2.c_str());
        valid_file_2 = instream.good();
        if (!valid_file_2) {
            cout << "Error: Invalid filename, please try again\n";
            cout << endl;
        }
    }

    array_2_size = read_file(array_2, instream);
    instream.close();

    cout << "The list of " << array_2_size << " numbers in file " << filename_2 << " is:\n";
    for (int i = 0; i < array_2_size; i++) {
        cout << array_2[i] << "\n";
    }
    cout << endl;

    int output_array[MAX_SIZE];
    int output_array_size = combine_and_sort(array_1, array_1_size, array_2, array_2_size, output_array);

    cout << "The sorted list of " << output_array_size << " numbers is:";
    for (int i = 0; i < output_array_size; i++) {
        cout << " " << output_array[i];
    }
    cout << endl;

    writefile(output_array, output_array_size);

    cout << "*** Goodbye. ***" << endl;
    return 0;
}