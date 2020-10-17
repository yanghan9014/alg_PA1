// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>
#include <stdlib.h>
#include <climits>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int n = data.size();
    if( n==1 )
        return;
    else{
        for(int j=1; j<n; j++){
            int key = data[j];
            int i = j-1;
            while(i >= 0 && data[i] > key){
                data[i+1] = data[i];
                i--;
            }
            data[i+1] = key;
        }
    }

}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);

}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    
    if(low < high){
    	int index = rand() % (high - low + 1) + low;
    	swap(data[index], data[high]);
    	
	int x = Partition(data, low, high);
   	QuickSortSubVector(data, low, x-1);
	QuickSortSubVector(data, x+1, high);
    }

}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int par = low;
    int key = data[high];
    for(int j=low ; j<high; j++){
	if(data[j] <= key){
	    //swapElement(data, j, par);
	    swap(data[j], data[par]);
		par++;
	}
    }
    //swapElement(data, high, par);
    swap(data[high], data[par]);
    return par;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);

}


// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high){
	int q = (low + high)/2;
	MergeSortSubVector(data, low, q);
	MergeSortSubVector(data, q + 1, high);
	Merge(data, low, q, q+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1 - low + 1;
    int n2 = high - middle2 + 1;
	vector<int> L;
	L.reserve(n1+1);
	vector<int> R;
	R.reserve(n2+1);

	for(int i=low; i<= middle1; i++){
        L.push_back(data[i]);
//cout << "L:" << data[i] << endl;
	}
	L.push_back(INT_MAX);
	
    for(int i=middle2; i<= high; i++){
	R.push_back(data[i]);
//	cout << "R:" << data[i] << endl;
    }//cout << endl;
    R.push_back(INT_MAX);
    int l = 0;
    int r = 0;
//	int k = low;
	for(int k = 0; k<n1 + n2; k++){
		if(L[l] <= R[r]){
			data[low + k] = L[l];
			l++;
		}
		else if(L[l] > R[r]){
			data[low + k] = R[r];
			r++;
		}

	}
    //vector<int> merged;
    /*
    while(l <= middle1 && r <= high){
		if(L[l] <= R[r]){
	    	data[k] = L[l];
	   		k++;
			l++;
		}
		else if(L[l] > R[r]){
			data[k] = R[r];
			k++;
			r++;
		}
    }
    if(l > middle1){
	    while(r <= high){
		data[k] = R[r];
	    	r++;
		k++;
	    }
    }
    else if(r > high){
	    while(l <= middle1){
		data[k] = L[l];
		l++;
		k++;
	    }
    }*/
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    for(int i=0; i<heapSize; i++){
	  //  cout << data[i] << "\t";
    }
   // cout << heapSize << endl;

    //for(int i=0; i<heapSize; i++)
	    //cout << data[i] << endl;
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0], data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
	int l = root * 2 + 1;
	int r = root * 2 + 2;
	//if(root < 10)
	//cout << "maxhepify_root:" << root << "=" << data[root] << "  left:" << l << "=" << data[l] << "  right:" << r << "=" << data[r];
	int largest = root;
	if( l <= heapSize - 1 && data[l] > data[largest] ){
		largest = l;
	}
	if( r <= heapSize - 1 && data[r] > data[largest]){
		largest = r;
	}
	//if(root < 10)
	//cout << "   largest:" << largest << endl;

	if(largest != root){
		swap(data[largest], data[root]);
		//swapElement(data, largest, root);
		MaxHeapify(data, largest);
	}
//	else
	//	cout << endl;
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
	for(int i = heapSize / 2 - 1; i>= 0; i--){
	//	cout << i << " " ;
		MaxHeapify(data, i);
	
	//if(i < 10)
	//cout << "maxhepify_root:" << i << "=" << data[i] << "  left:" << 2*i + 1 << "=" << data[2*i+1] << "  right:" << 2*i+2 << "=" << data[2*i+2] << endl;
	}
}
