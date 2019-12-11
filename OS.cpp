#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include <bits/stdc++.h>
using namespace std; 

int fsize[10],fstart[10],freest[10],freesize[10],m=0,n=0,start,readonly[10];
char fname[10];
void create(char,int,int); 
void del(char); 
void compaction(); 
void display(); 
void delete_line(const char* ,char);
void sort();
int run_size();
void sorted_display();

int main()
{
	int size,ch,i,security,s,k=0; 
    char name;
	int *ptr;
	system("cls");
    ptr = (int*) malloc(5*sizeof(int));
	start=freest[0]=*ptr;
    freesize[0]=500;
	cout<<"\n\nFree start address         Free Size      \n";
	for(i=0;i<=m;i++) 
       cout<<freest[i]<<"                    "<<freesize[i]<<endl; 
       cout<<"\n\n"; 
      while(1) 
    { 

    cout<<"\n1.Create.\n";
    cout<<"2.Delete.\n"; 
    cout<<"3.Compaction.\n"; 
    cout<<"4.Display FAT.\n";
   	cout<<"5.Check FAT\n";
    cout<<"6.Sort accoriding to Name\n";
	cout<<"7.Display sorted FAT\n";
	cout<<"8.Exit.\n";
	cout<<"Enter your choice: "; 
    cin>>ch;
    switch(ch) 
       { 
        case 1: 
        	k++;
            cout<<"\nEnter the name of file: "; 
            cin>>name; 
            cout<<"\nEnter the size of the file: "; 
            cin>>size; 
	        cout<<"\nDo you want the file as read only: input 1 or 0 "; 
              cin>>security;
            create(name,size,security); 
	    	cout<<"\n";
	    	cout<<"-----------------------------------------------------------------------";
        	break; 
        case 2: 
            cout<<"\nEnter the file name which u want to delete: "; 
            cin>>name;
            del(name); 
	    	cout<<"-----------------------------------------------------------------------";
            break; 
         case 3: 
             compaction(); 
             cout<<"\nAfter compaction the tables will be:\n"; 
             display(); 
             cout<<"-----------------------------------------------------------------------";
             break; 
	 case 4:
	      display();
	      cout<<"-----------------------------------------------------------------------";
	      break;
    case 5:
	      display();
	      cout<<"-----------------------------------------------------------------------";
	      break;
	case 6:
		sort();
		cout<<"-----------------------------------------------------------------------";
		break;
	case 7:
		sorted_display();
		cout<<"-----------------------------------------------------------------------";
	    break;
	case 8: 
        exit(1); 
    default: 
        cout<<"\nYou have entered a wrong choice.\n"; 
       } 
    } 

 } 

 void create(char name,int size,int security) 
	{ 
    fstream file;
    file.open("input.txt",ios :: app|ios::binary);
	file<<name<<" ";
	file.close();
	fstream data;
	data.open("data.txt",ios :: app);
	data<<name<<" "<<size<<" "<<security<<"\n";
	data.close();
	int i,flag=1,j,a; 
    for(i=0;i<=m;i++)	
    	if( freesize[i] >= size) 
       		a=i,flag=0; 
    if(!flag) 
       { 
     	for(j=0;j<n;j++); 
        	n++; 
     	fname[j]=name; 
     	fsize[j]=size;
     	readonly[j]=security; 
     	fstart[j]=freest[a]; 
     	freest[a]=freest[a]+size; 
     	freesize[a]=freesize[a]-size; 
     	cout<<"\nMEMORY ALLOCATED:\n";
     	cout<<"From: "<<fstart[j]<<"  To: "<<freest[a]<<endl;
       } 
    else 
       { 
    	cout<<"\nNot enough space is available.System compaction......";  
        flag=1; 
		compaction(); 
        display(); 
    	for(i=0;i<=m;i++) 
           if( freesize[i] >= size) 
        a=i,flag=0; 
    	if(!flag) 
    		{
			for(j=0;j<n;j++); 
          		n++; 
       		fname[j]=name; 
       		fsize[j]=size; 
       		readonly[j]=security;
       		fstart[j]=freest[a]; 
       		freest[a]+=size; 
       		freesize[a]-=size; 
       		cout<<"\n The memory map will now be: \n\n"; 
       		display(); 
      		} 
     	else 
     		cout<<"\nNo enough space.\n"; 
       } 
  	} 

void del(char name) 
  { 
    int i,j,k,flag=1; 
     for(i=0;i<n;i++) 
       if(fname[i]==name) 
           break; 
     if(i==n) 
       { 
    flag=0; 
    cout<<"\nNo such process exists\n"; 
       }
	if(readonly[i]==1)
	{
	flag=0;
	cout<<"\nFile is read only, cannot be deleated\n"; 
    }
    else 
       { 
       delete_line("data.txt",name);
	   m++; 
       freest[m]=fstart[i]; 
       freesize[m]=fsize[i]; 
     	for(k=i;k<n;k++) 
            { 
        	fname[k]=fname[k+1]; 
        	fsize[k]=fsize[k+1]; 
          	fstart[k]=fstart[k+1]; 
            } 
        n--; 
       } 
    if(flag) 
    	{ 
     	cout<<"\nFile "<<name<<" deleted\n\n";
       	} 
   } 

void compaction() 
  { 
    int i,j,size1=0,f_size=0; 
    if(fstart[0]!=start) 
       	{ 
    	fstart[0]=start; 
    	for(i=1;i<n;i++) 
    		fstart[i]=fstart[i-1]+fsize[i-1]; 
      	} 
    else 
       	{ 
      	for(i=1;i<n;i++) 
       		fstart[i]=fstart[i-1]+fsize[i-1]; 
       	}	 
     	f_size=freesize[0]; 

     	for(j=0;j<=m;j++) 
       		size1+=freesize[j]; 
      	freest[0]=freest[0]-(size1-f_size); 
      	freesize[0]=size1; 
      	m=0; 
 } 

void display() 
    { 
     int i; 
      
     cout<<"\nMEMORY MAP TABLE\n"; 
     cout<<"\n\nNAME     SIZE    ACCESS TYPE (1-READ ONLY , 2- READ AND WRITE)      \n\n"; 
	std::ifstream is ("data.txt", std::ifstream::in);
	char word; 
	while (is.get(word))
		cout<<word;
   is.close();
   }

void delete_line(const char *file_name, char n) 
{ 
  
    std::ifstream is (file_name, std::ifstream::in);
  
    ofstream ofs; 
    ofs.open("temp.txt", ofstream::app); 
   
    char k='\n';
	char word; 
	while (is.get(word))
    {
	if ((word==n)&&(k=='\n')) 
		while(word!='\n')
			is.get(word); 
   	else
   		{
   		ofs<<word;
   		cout<<word;
   		}
	k=word;   
    }

    ofs.close(); 

    is.close(); 

    remove(file_name); 

    rename("temp.txt", file_name); 
}

struct MinHeapNode 
{ 

    int element; 

    int i; 
}; 

void swap(MinHeapNode* x, MinHeapNode* y); 

class MinHeap 
{ 
    MinHeapNode* harr; 
    int heap_size;   
  
public: 
   
    MinHeap(MinHeapNode a[], int size); 

    void MinHeapify(int); 

    int left(int i) { return (2 * i + 1); } 
 
    int right(int i) { return (2 * i + 2); } 
 
    MinHeapNode getMin() {  return harr[0]; } 

    void replaceMin(MinHeapNode x) 
    { 
        harr[0] = x; 
        MinHeapify(0); 
    } 
}; 

MinHeap::MinHeap(MinHeapNode a[], int size) 
{ 
    heap_size = size; 
    harr = a; 
    int i = (heap_size - 1) / 2; 
    while (i >= 0) 
    { 
        MinHeapify(i); 
        i--; 
    } 
} 

void MinHeap::MinHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < heap_size && harr[l].element < harr[i].element) 
        smallest = l; 
    if (r < heap_size && harr[r].element < harr[smallest].element) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&harr[i], &harr[smallest]); 
        MinHeapify(smallest); 
    } 
} 

void swap(MinHeapNode* x, MinHeapNode* y) 
{ 
    MinHeapNode temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 

    int L[n1], R[n2]; 

    for(i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for(j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 

    i = 0; 
    j = 0;
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
            arr[k++] = L[i++]; 
        else
            arr[k++] = R[j++]; 
    } 

    while (i < n1) 
        arr[k++] = L[i++]; 

    while(j < n2) 
        arr[k++] = R[j++]; 
} 

void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
       
        int m = l + (r - l) / 2; 

        mergeSort(arr, l, m); 
        mergeSort(arr, m + 1, r); 
  
        merge(arr, l, m, r); 
    } 
} 
  
FILE* openFile(char* fileName, char* mode) 
{ 
    FILE* fp = fopen(fileName, mode); 
    if (fp == NULL) 
    { 
        perror("Error while opening the file.\n"); 
        exit(EXIT_FAILURE); 
    } 
    return fp; 
} 
  
void mergeFiles(char *output_file, int n, int k) 
{ 
    FILE* in[k]; 
    for (int i = 0; i < k; i++) 
    { 
        char fileName[2]; 

        snprintf(fileName, sizeof(fileName), "%d", i); 

        in[i] = openFile(fileName, "r"); 
    } 

    FILE *out = openFile(output_file, "w"); 

    MinHeapNode* harr = new MinHeapNode[k]; 
    int i; 
    for (i = 0; i < k; i++) 
    { 
 
        if (fscanf(in[i], "%d ", &harr[i].element) != 1) 
            break; 
  
        harr[i].i = i; 
    } 
    MinHeap hp(harr, i); 
  
    int count = 0; 

    while (count != i) 
    { 
       
        MinHeapNode root = hp.getMin(); 
        fprintf(out, "%d ", root.element); 

        if (fscanf(in[root.i], "%d ", &root.element) != 1 ) 
        { 
            root.element = INT_MAX; 
            count++; 
        } 

        hp.replaceMin(root); 
    } 

    for (int i = 0; i < k; i++) 
        fclose(in[i]); 
  
    fclose(out); 
} 

void createInitialRuns(char *input_file, int run_size, 
                       int num_ways) 
{ 

    FILE *in = openFile(input_file, "r"); 

    FILE* out[num_ways]; 
    char fileName[2]; 
    for (int i = 0; i < num_ways; i++) 
    { 
     
        snprintf(fileName, sizeof(fileName), "%d", i); 

        out[i] = openFile(fileName, "w"); 
    } 

    int* arr = (int*)malloc(run_size * sizeof(int)); 
  
    bool more_input = true; 
    int next_output_file = 0; 
  
    int i; 
    while (more_input) 
    { 
 
        for (i = 0; i < run_size; i++) 
        { 
            if (fscanf(in, "%d ", &arr[i]) != 1) 
            { 
                more_input = false; 
                break; 
            } 
        } 

        mergeSort(arr, 0, i - 1); 

        for (int j = 0; j < i; j++) 
            fprintf(out[next_output_file], "%d ", arr[j]); 
  
        next_output_file++; 
    } 

    for (int i = 0; i < num_ways; i++) 
        fclose(out[i]); 
  
    fclose(in); 
} 
  
void externalSort(char* input_file,  char *output_file, 
                  int num_ways, int run_size) 
{ 
 
    createInitialRuns(input_file, run_size, num_ways); 
    mergeFiles(output_file, run_size, num_ways); 
} 
  
void sort() 
{ 
    int num_ways = 10; 
    int run_siz = run_size(); 
    char input_file[] = "input.txt"; 
    char output_file[] = "output.txt"; 
  
    externalSort(input_file, output_file, num_ways, 
                run_siz); 
  
}

int run_size()
{
std::ifstream is ("input.txt", std::ifstream::in);
char s;
int sum=0,k;
while(is.get(s))
	{
	if((s!=' ')&&(s!='\n'))
	{
	k=s-'0';
	sum+=k;
	}
	}
is.close();
return(sum);
}

void sorted_display()
{ 
    int i; 
      
    cout<<"\nSORTED MEMORY MAP TABLE\n"; 
    cout<<"\n\nNAME     SIZE    ACCESS TYPE      \n\n"; 
	std::ifstream it ("output.txt", std::ifstream::in);

	char w1,w2,k='\n'; 
	while (it.get(w1))
	{
		std::ifstream ot ("data.txt", std::ifstream::in);
		while(ot.get(w2))
			{
			if (w1==w2)
				{
				while(w2!='\n')
					{
					cout<<w2;
					ot.get(w2);
					}
				cout<<endl;
				}
			else
				{
					while(w2!='\n')
					{
					ot.get(w2);
				}
			}
			}
		ot.close();
	}
	it.close();
	
}
