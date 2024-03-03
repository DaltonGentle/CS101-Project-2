#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

// Function prototypes
void merge(int numbers[], int i, int j, int k);
void merge_sort(int numbers[], int i, int k);
int partition(string words[], int i, int k);
void quick_sort(string words[], int i, int k);

void merge(int numbers[], int i, int j, int k) {
    int merged_size = k - i + 1;
    int merge_pos = 0;
    int left_pos = i;
    int right_pos = j + 1;
    int* merged_numbers = new int[merged_size];

    while (left_pos <= j && right_pos <= k) {
        if (numbers[left_pos] < numbers[right_pos]) {
            merged_numbers[merge_pos] = numbers[left_pos];
            ++left_pos;
        } else {
            merged_numbers[merge_pos] = numbers[right_pos];
            ++right_pos;
        }
        ++merge_pos;
    }

    while (left_pos <= j) {
        merged_numbers[merge_pos] = numbers[left_pos];
        ++left_pos;
        ++merge_pos;
    }

    while (right_pos <= k) {
        merged_numbers[merge_pos] = numbers[right_pos];
        ++right_pos;
        ++merge_pos;
    }

    for (merge_pos = 0; merge_pos < merged_size; ++merge_pos) {
        numbers[i + merge_pos] = merged_numbers[merge_pos];
    }

    delete[] merged_numbers;
}

void merge_sort(int numbers[], int i, int k) {
    if (i < k) {
        int j = (i + k) / 2;
        merge_sort(numbers, i, j);
        merge_sort(numbers, j + 1, k);
        merge(numbers, i, j, k);
    }
}

int partition(string words[], int i, int k) {
    int l = i;
    int h = k;
    int midpoint = i + (k - i) / 2;
    string pivot = words[midpoint];
    string temp;
    bool done = false;

    while (!done) {
        while (words[l] < pivot) {
            ++l;
        }

        while (pivot < words[h]) {
            --h;
        }

        if (l >= h) {
            done = true;
        } else {
            temp = words[l];
            words[l] = words[h];
            words[h] = temp;

            ++l;
            --h;
        }
    }

    return h;
}

void quick_sort(string words[], int i, int k) {
    if (i >= k) {
        return;
    }

    int j = partition(words, i, k);
    quick_sort(words, i, j);
    quick_sort(words, j + 1, k);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " [i|s] file1 file2" << endl;
        return 1;
    }

    string sort_type = argv[1];
    string input_file1 = argv[2];
    string input_file2 = argv[3];

    // Read data from files
    ifstream file1(input_file1);
    ifstream file2(input_file2);

    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Error opening one or more input files." << endl;
        return 1;
    }

    // Create arrays to store data
    const int MAX_ITEMS = 20000; // Maximum number of data items
    int numbers[MAX_ITEMS];
    int numbers2[MAX_ITEMS];
    string words[MAX_ITEMS];
    string words2[MAX_ITEMS];
    const int MAX_DUPLICATES = 20000; // Maximum number of duplicate values
    int duplicates[MAX_DUPLICATES];
    string dupliates_string[MAX_DUPLICATES];
    int index_duplicates = 0;

    // Read and store data from file1
    int num1, index1 = 0;
    string word1;
    while ((sort_type == "i" && file1 >> num1) || (sort_type == "s" && file1 >> word1)) {
        if (sort_type == "i") {
            numbers[index1++] = num1;
        } else {
            words[index1++] = word1;
        }
    }

    // Read and store data from file2
    int num2, index2 = 0;
    string word2;
    while ((sort_type == "i" && file2 >> num2) || (sort_type == "s" && file2 >> word2)) {
        if (sort_type == "i") {
            numbers2[index2++] = num2;
        } else {
            words2[index2++] = word2;
        }
    }


    file1.close();
    file2.close();

    // Sort the arrays based on the specified type
    if (sort_type == "i") {
        merge_sort(numbers, 0, index1 - 1);
        merge_sort(numbers2, 0, index2 - 1);

        // Compare the sorted arrays for common values
        int i = 0, j = 0;
        while (i < index1 && j < index2) {
            if (numbers[i] == numbers2[j]) {
                // Check if the duplicate value is not already in the duplicates array
                bool isDuplicate = false;
                for (int k = 0; k < index_duplicates; ++k) {
                    if (duplicates[k] == numbers[i]) {
                        isDuplicate = true;
                        break;
                    }
                }

                // If not a duplicate, store it in the duplicates array
                if (!isDuplicate) {
                    duplicates[index_duplicates++] = numbers[i];
                }

                // Move to the next values in both arrays
                ++i;
                ++j;
            } else if (numbers[i] < numbers2[j]) {
                ++i;
            } else {
                ++j;
            }
        }

        // Output the duplicate values
        for (int k = 0; k < index_duplicates; ++k) {
            cout << duplicates[k] << endl;
        }
    } 
    else if (sort_type == "s") {
        quick_sort(words, 0, index1 - 1);
        quick_sort(words2, 0, index2 - 1);

        // Compare the sorted arrays for common values
        int i_str = 0, j_str = 0;
        while (i_str < index1 && j_str < index2) {
            int compare_result = strcmp(words[i_str].c_str(), words2[j_str].c_str());

            if (compare_result == 0) {
                // Check if the duplicate value is not already in the duplicates array
                bool isDuplicate = false;
                for (int k = 0; k < index_duplicates; ++k) {
                    if (strcmp(dupliates_string[k].c_str(), words[i_str].c_str()) == 0) {
                        isDuplicate = true;
                        break;
                    }
                }

                // If not a duplicate, store it in the duplicates array
                if (!isDuplicate) {
                    dupliates_string[index_duplicates++] = words[i_str];
                }

                // Move to the next values in both arrays
                ++i_str;
                ++j_str;
            } else if (compare_result < 0) {
                ++i_str;
            } else {
                ++j_str;
            }
        }

        // Output the duplicate values for strings
        for (int k = 0; k < index_duplicates; ++k) {
            cout << dupliates_string[k] << endl;
        }
    }

    return 0;
}