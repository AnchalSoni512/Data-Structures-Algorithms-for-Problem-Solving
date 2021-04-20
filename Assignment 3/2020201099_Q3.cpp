#include<iostream>
#include<string>
#include<error.h>
#include <bits/stdc++.h> 
using namespace std;
#define chunksize 1000000
// #define chunksize 5000
#define lli long long int
bool more_chunk = false;
lli remain = 0;
lli wordcount2=0,wordcount3=0;
lli leftsize =0;
lli rightsize =0;

FILE* openFile(char* fileName, char* mode) 
{ 
	FILE* fp = fopen(fileName, mode); 
	if (fp == NULL) { 
		perror("Error while opening the file.\n"); 
		exit(EXIT_FAILURE); 
	} 
	return fp;
	 
}

void closeFile(FILE *fp)
{
   int chk = fclose(fp);
   if(chk != 0)
    { 
		perror("Error while closing the file.\n"); 
		exit(EXIT_FAILURE); 
	} 

}

void mergeSort(vector<lli>&left, vector<lli>& right, vector<lli>& bars, lli sl, lli sr, lli sb)
{
    lli nL = left.size();
    lli nR = right.size();
    lli i = 0, j = 0, k = 0;
    if(sl != 0)
	sl--;
    while (j < nL && k < nR) 
    {
        if (left[j] < right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
	if(sr != 0)
	sr--;
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
	if(sb != 0)
	sb--;
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}


void sortarray(vector<lli> & bar) 
{
    if (bar.size() <= 1) 
	return;
    else
	{
		lli mid = bar.size() / 2;
		vector<lli> left;
		vector<lli> right;
		leftsize= left.size();
		rightsize= right.size();
		for (size_t j = 0; j < mid;j++)
			left.push_back(bar[j]);
		for (size_t j = 0; j < (bar.size()) - mid; j++)
			right.push_back(bar[mid + j]);

		sortarray(left);
		if(leftsize != 0)
		leftsize--;
		sortarray(right);
		if(rightsize != 0)
		rightsize--;
		mergeSort(left, right, bar , left.size(), right.size(), bar.size() );
	}
	
    
}

class node
{
public:
	lli data;
	lli fileno;
};
class minheap
{
public:
	node* arr;
	lli heap_size;
public:
	minheap(node n[], lli k)
	{
		arr = n;
		heap_size = k;
		lli i = (heap_size - 1) / 2; 
		while (i >= 0) 
		{ 
		heapify(i); 
		i--; 
	    } 
	}
	node findmin()
	{
		return arr[0];
	}
	void rearrange(node n)
	{
		arr[0] = n;
		heapify(0);
	}
	lli getleft(lli x) { return (2 * x + 1); }
	lli getright(lli x) { return (2 * x + 2); }
	void swap(node* x, node* y)
	{
		node temp = *x; 
		*x = *y; 
		*y = temp; 
	}
	void heapify(lli x)
	{
		lli l = getleft(x);
		lli r = getright(x);
		lli data1 = arr[x].data;
		lli min = x;
		node temp;
		if (l < heap_size && arr[l].data < data1)
			min = l;
		if (r < heap_size && arr[r].data < arr[min].data)
			min = r;
		if (min != x)
		{
			// temp = arr[min];
			// arr[min] = arr[x];
			// arr[x] = temp;
			swap(&arr[min], &arr[x]);
			heapify(min);
		}
	}
};

void kwaymerge(char* of, lli nf)
{
	//cout<<"inside merge"<<endl;
	FILE* fptr[nf];
	char mode[2] = "w";
	FILE* fp = openFile(of, mode);
	node* n = new node[nf];
	lli i = 0, j;
	for (j = 0; j < nf; j++)
	{
		string fname = "file" + to_string(j);
		char ch[500];
		strcpy(ch, fname.c_str());
		char mode[2] = "r";
		fptr[j] = openFile(ch, mode);
		fscanf(fptr[j], "%lld,", &n[i].data);
		n[i].fileno = i;
		i++;
	}

	minheap h(n, nf);
	node root;

	lli cnt = 0;
	if (more_chunk == true)
		cnt = chunksize * (nf - 1) + remain;
	else
	    cnt = chunksize * nf;

	for (lli m = 0; m < cnt; m++)
	{
		root = h.findmin();
		wordcount2++;
		lli x = root.data;
		lli f = root.fileno;
		//cout<<"x: "<<x<<" f: "<<f<<endl;
		if(wordcount2 < wordcount3)
		fprintf(fp, "%lld,", x);
		else
		fprintf(fp, "%lld", x);	
		if (fscanf(fptr[f], "%lld,", &root.data) == EOF)
			root.data = LLONG_MAX;

		h.rearrange(root);
	}

	for (lli m = 0; m < nf; m++)
		closeFile(fptr[m]);

	closeFile(fp);

}
lli dividefiles(char* f)
{
    fstream file(f);
	lli cnt = 0,wordcount=0;
	string s;
	while (getline(file, s, ','))
		wordcount++;
	file.close();
	wordcount3=wordcount;
	lli nfiles = wordcount / chunksize;
	if (wordcount % chunksize != 0)
	{
		remain = wordcount % chunksize;
		more_chunk = true;
	}
	char mode[2] = "r";
	FILE *fp = openFile(f,mode);
	FILE *fptr[nfiles+1];
	lli i,j;
	for(i=0;i<nfiles;i++)
	{
		vector<lli> arr;
		lli val;
		for(j=0;j<chunksize;j++)
		{
			fscanf(fp,"%lld,",&val);
			arr.push_back(val);
		}
		sortarray(arr);
		string fname ="file"+to_string(i);
		char c[500];
		strcpy(c,fname.c_str());
		char mode[2] = "w";
		fptr[i]=openFile(c,mode);
		for(lli j=0;j<chunksize;j++)
			fprintf(fptr[i],"%lld,",arr[j]);
		closeFile(fptr[i]);
	}
	if(more_chunk==true) // when last chunksize<chunksize
	{
		vector<lli> arr;
		lli val;
		//lli arr[remain];
		for(j=0;j<remain;j++)
		{
			fscanf(fp,"%lld,",&val);
			arr.push_back(val);
		}
		sortarray(arr);
		string fname="file"+to_string(i);
		char c[500];
		strcpy(c,fname.c_str());
		char mode[2] = "w";
		fptr[i]=openFile(c,mode);
		for(lli j=0;j<remain-1;j++)
			fprintf(fptr[i],"%lld,",arr[j]);
		fprintf(fptr[i],"%lld",arr[j]);
		closeFile(fptr[i]);
		nfiles++;
	}
	closeFile(fp);
    return nfiles;
}

void startExternalMsort(char* f, char* of)
{
	lli nfiles = dividefiles(f);
	kwaymerge(of,nfiles);
}

int main(int argc, char** argv)
{
	char* input_file;
	char* output_file;
	if (argc != 3)
	{
		cout << "ERROR in input: Provide input.txt and output.txt as command line argument" << endl;
		exit(0);
	}
	input_file = argv[1];
	output_file = argv[2];
	startExternalMsort(input_file, output_file);
}