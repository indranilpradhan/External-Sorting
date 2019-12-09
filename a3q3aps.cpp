#include <bits/stdc++.h>
using namespace std;
#define ll long long int
struct heapify
{
	ll filptr;
	ll value;
};

//ll c[40];

void mergesort(ll a[],ll low, ll mid, ll high)
{
	ll c[1000];
	ll i = low;
	ll j = mid+1;
	ll k = low;
	while(i<=mid && j<=high)
	{
		if(a[i] < a[j])
			c[k++] = a[i++];
		else
			c[k++] = a[j++];
	}

	while(i <= mid)
		c[k++] = a[i++];
	while(j <= high)
		c[k++] = a[j++];
	for(ll p=low; p<=high; p++)
	{
		a[p] = c[p];
	}
}

void merge(ll a[],ll low, ll high)
{
	ll mid;
	if(low != high)
	{
		mid = (low + high) / 2;
		merge(a,low,mid);
		merge(a,mid+1,high);
		mergesort(a,low, mid, high);
	}
}

void insertheap(struct heapify heap[],struct heapify newheap, ll location)
{
	ll parent;
//	int filptr = location;
	while(location > 0)
	{
		parent = (location - 1)/2;
		if(newheap.value <= heap[parent].value)
		{
			heap[location] = newheap;
			return;
		}
		heap[location] = heap[parent];
		location = parent;
	}
	heap[0] = newheap;
}

void minheap(struct heapify heap[],ll last)
{
	//	cout<<"here"<<endl;
	ll minele, right, left, i=0;
	heapify temp;
	temp = heap[i];
	heap[i] = heap[last];
	heap[last] = temp;
	left = 2*i + 1;
	right = 2*i + 2;
	//int lastloc = sizeof(heap)/sizeof(heap[0]) - 1;
	while(right < last)
	{
		if(heap[i].value >= heap[left].value && heap[i].value >= heap[right].value)
			return;
		if(heap[right].value <= heap[left].value)
		{
			temp = heap[i];
			heap[i] = heap[left];
			heap[left] = temp;
			i = left;
		}
		else
		{
			temp = heap[i];
			heap[i] = heap[right];
			heap[right] = temp;
			i = right;
		}
		left = 2*i + 1;
		right = 2*i + 2;
	}
	if(left == last-1 && heap[i].value < heap[left].value)
	{
		temp = heap[i];
		heap[i] = heap[left];
		heap[left] = temp;
	}
}

int main(int argc, char** argv)
{
	char input[100];
	char output[100];
	strcpy(input,argv[1]);
	strcpy(output, argv[2]);
	ll chunksize = 1000;
	ll count =0;
	ll outptrcount = 0;
	FILE* infp = fopen(input, "r");

	ifstream file(input);
	string line;
    while (getline(file, line))
        count++;
    file.close();

    ll loopcount = count / chunksize;
    ll rem = count % chunksize;

    if(rem == 0)
    	outptrcount = loopcount;
    else
    	outptrcount = loopcount + 1;

    FILE* outptrfile[outptrcount];
  //  cout<<"outptrcount "<<outptrcount<<endl;
    char outfile[100000]; 
    for (ll i = 0; i < outptrcount; i++) 
    {  
        snprintf(outfile, sizeof(outfile), "%lld", i);  
        outptrfile[i] = fopen(outfile, "w"); 
    } 
    memset(outfile,0, sizeof(outfile));
    ll sortarr[chunksize];
    heapify heap[outptrcount];
  //  cout<<loopcount<<endl;
    ll currptr=0;
    ll l=0;
    while(loopcount > 0)
    {
    	for(ll i=0; i<chunksize; i++)
    	{
    		fscanf(infp,"%lld", &sortarr[i]);
    	//	cout<<sortarr[i]<<endl;
    	}
   // 	 cout<<"here"<<l++<<endl;
    	merge(sortarr,0,chunksize-1);
   // 	cout<<"here 2"<<endl;
    	for(ll i = 0; i<chunksize ; i++)
    	{
    //		cout<<currptr<<" "<<sortarr[i]<<endl;
    		fprintf(outptrfile[currptr],"%lld\n", sortarr[i]);
    	}
   // 	cout<<"currptr "<<currptr<<endl;
    	currptr++;
    	loopcount--;
    	memset(sortarr,0, sizeof(sortarr));
    }
    //cout<<rem<<endl;
    if(rem  != 0)
    {
    	ll nsortarr[rem];
  //  	cout<<"rem "<<rem;
    	for(ll i=0; i<rem; i++)
    	{
    		fscanf(infp,"%lld", &nsortarr[i]);
    	}

    	merge(nsortarr,0,rem-1);

    	for(ll i = 0; i<rem ; i++)
    	{
  	 		fprintf(outptrfile[currptr],"%lld\n", nsortarr[i]);
    	}
    } 

    for (ll i = 0; i < outptrcount; i++) 
    {  
        fclose(outptrfile[i]); 
    }  

    for (ll i = 0; i < outptrcount; i++) 
    {  
        snprintf(outfile, sizeof(outfile), "%lld", i);  
        outptrfile[i] = fopen(outfile, "r"); 
    } 

    ll element =0;

	for(ll i=0; i<outptrcount; i++)
    {
    	fscanf(outptrfile[i],"%lld", &element);
    //	cout<<"element "<<element<<endl;
    	heapify newheap;
    	newheap.value = element;
    	newheap.filptr = i;
    	insertheap(heap,newheap,i);
    } 

    FILE* outfp = fopen(output, "w");
    ll filecount = outptrcount;

    while(count > 0)
    {

		for(ll i =filecount-1 ; i>=0;i--)
		{
			minheap(heap,i);
		}

		// for(int i =0 ; i<filecount;i++)
		// {
		// 	cout<<heap[i].value<<" ";;
		// }

		heapify retheap = heap[0];
		//	cout<<"popped "<<retheap.value<<endl;
		fprintf(outfp, "%lld\n", retheap.value);
		ll ele;
		heapify newheap;
		if(fscanf(outptrfile[retheap.filptr], "%lld", &ele) != 1)
		{
			heap[0].value = LONG_MAX; 
		//	cout<<"new ele "<<ele<<endl;
		}
		else
		{
			newheap.filptr = retheap.filptr;
			newheap.value = ele;
			heap[0] = heap[filecount-1];
//		if(filecount > count)
//			filecount = count;
			heap[filecount-1] = newheap;
		}
		count--;
		//insertheap(heap,newheap,0);
		//count--;
		//if(filecount > count)
		//	filecount = count;
    }

    for (ll i = 0; i < outptrcount; i++) 
    {  
        fclose(outptrfile[i]); 
    }  
    fclose(outfp);
    fclose(infp);
	return 0;
}
