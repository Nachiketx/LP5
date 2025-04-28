#include<iostream>
#include<omp.h>
#include<vector>
using namespace std;

class MergeSort{
    public:
    vector<int> data;
    void merge(int start1, int end1, int start2, int end2){
        vector<int> temp;

        int i = start1, j =start2;

        while(i <= end1 && j <= end2){
            if(data[i] < data[j]){
                temp.push_back(data[i]);
                i++;
            } else {
                temp.push_back(data[j]);
                j++;
            }
        }

    }

    MergeSort(vector<int> input){
        this->data = input;
    }
    void sequentialSort(){
        int n = data.size();
        sequentialMergeSort(0, n-1);
    }
    void sequentialMergeSort(int start, int end){
        if(start < end){
            int mid = (start + end) / 2;
            sequentialMergeSort(start, mid);
            sequentialMergeSort(mid+1, end);
            merge(start,mid,mid+1,end);
        }
    }
};

int main(int argc, char const *argv[])
{
    


    return 0;
}