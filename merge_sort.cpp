#include "sorts.h"
using namespace std;

void merge(vector<string>& arr,int left,int mid,int right) {
    vector<string> temp;
    int i=left;
    int j=mid+1;
    while (i<=mid && j<=right) {
        if (arr[i]<=arr[j]) {
            temp.push_back(arr[i]);
            i++;
        }
        else {
            temp.push_back(arr[j]);
            j++;
        }
    }
    while (i<=mid) {
        temp.push_back(arr[i]);
        i++;
    }
    while (j<=right) {
        temp.push_back(arr[j]);
        j++;
    }
    for (int k=0;k<temp.size();k++) {
        arr[left+k]=temp[k];
    }
}
void mergeSortPart(vector<string>& arr,int left,int right) {
    if (left>=right) {
        return;
    }
    int mid=(left+right)/2;
    mergeSortPart(arr,left,mid);
    mergeSortPart(arr,mid+1,right);
    merge(arr,left,mid,right);
}

bool mergeSort(const vector<string>& data,vector<string>& result) {
    if (data.empty()) {
        return false;
    }
    result=data;
    mergeSortPart(result,0,result.size()-1);
    return true;
}