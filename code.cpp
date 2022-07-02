#include<bits/stdc++.h>

using namespace std;

vector<char> unichar(string s){
    int n = s.size();
    vector<char> c;
    vector<int> b(96,0);
    for(int i=0;i<n;i++){
        b[s[i]-' ']=1;
    }
    for(int i=0;i<96;i++){    
        if(b[i]==1){
            char j = ' '+i;
            c.push_back(j);
        }
    }
    return c;
}

vector<int> getfreq(vector<char> &c, string s){
    int n = c.size();
    int m = s.size();
    vector<int> freq(n,0);
    vector<int> f(96,0);
    for(int i=0;i<m;i++){
        f[s[i]-' ']++;
    }
    for(int i=0,j=0;i<96;i++){
        char k = ' '+i;
        if(k==c[j]){
            freq[j]=f[i];
            j++;
        }
    }
    return freq;
}

void merge(vector<int> &array,vector<char> &c, int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
 
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}
 
// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(vector<int> &array,vector<char> &c, int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively
 
    auto mid = begin + (end - begin) / 2;
    mergeSort(array,c, begin, mid);
    mergeSort(array,c, mid + 1, end);
    merge(array,c, begin, mid, end);
}

int main(){
    string s;
    getline (cin, s);
    vector<char> c = unichar(s);
    vector<int> freq = getfreq(c,s);

    int n = c.size();
    for(int i=0;i<n;i++){
        cout<<c[i]<<" "<<freq[i]<<endl;
    }
}