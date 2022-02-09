/* 
#include <bits/stdc++.h> 
using namespace std; 
  
struct Process { 
    int processID; 
    int burstTime; 
    int tempburstTime; 
    int responsetime; 
    int arrivalTime; 
    int priority; 
    int outtime; 
    int intime; 
}; 
  
// It is used to include all the valid and eligible 
// processes in the heap for execution. heapsize defines 
// the number of processes in execution depending on 
// the current time currentTime keeps a record of 
// the current CPU time. 
void insert(Process Heap[], Process value, int* heapsize, 
            int* currentTime) 
{ 
    int start = *heapsize, i; 
    Heap[*heapsize] = value; 
    if (Heap[*heapsize].intime == -1) 
        Heap[*heapsize].intime = *currentTime; 
    ++(*heapsize); 
  
    // Ordering the Heap 
    while (start != 0 && Heap[(start - 1) / 2].priority >  
                                  Heap[start].priority) { 
        Process temp = Heap[(start - 1) / 2]; 
        Heap[(start - 1) / 2] = Heap[start]; 
        Heap[start] = temp; 
        start = (start - 1) / 2; 
    } 
} 
  
// It is used to reorder the heap according to 
// priority if the processes after insertion 
// of new process. 
void order(Process Heap[], int* heapsize, int start) 
{ 
    int smallest = start; 
    int left = 2 * start + 1; 
    int right = 2 * start + 2; 
    if (left < *heapsize && Heap[left].priority < 
                            Heap[smallest].priority) 
        smallest = left; 
     if (right < *heapsize && Heap[right].priority <  
                           Heap[smallest].priority) 
        smallest = right; 
  
    // Ordering the Heap 
    if (smallest != start) { 
        Process temp = Heap[smallest]; 
        Heap[smallest] = Heap[start]; 
        Heap[start] = temp; 
        order(Heap, heapsize, smallest); 
    } 
} 
  
// This function is used to find the process with 
// highest priority from the heap. It also reorders 
// the heap after extracting the highest priority process. 
Process extractminimum(Process Heap[], int* heapsize, 
                       int* currentTime) 
{ 
    Process min = Heap[0]; 
    if (min.responsetime == -1) 
        min.responsetime = *currentTime - min.arrivalTime; 
    --(*heapsize); 
    if (*heapsize >= 1) { 
        Heap[0] = Heap[*heapsize]; 
        order(Heap, heapsize, 0); 
    } 
    return min; 
} 
  
// Compares two intervals according to staring times. 
bool compare(Process p1, Process p2) 
{ 
    return (p1.arrivalTime < p2.arrivalTime); 
} 
  
// This function is responsible for executing 
// the highest priority extracted from Heap[]. 
void scheduling(Process Heap[], Process array[], int n, 
                int* heapsize, int* currentTime) 
{ 
    if (heapsize == 0) 
        return; 
  
    Process min = extractminimum(Heap, heapsize, currentTime); 
    min.outtime = *currentTime + 1; 
    --min.burstTime; 
    printf("process id = %d current time = %d\n", 
           min.processID, *currentTime); 
  
    // If the process is not yet finished 
    // insert it back into the Heap* 
    if (min.burstTime > 0) { 
        insert(Heap, min, heapsize, currentTime); 
        return; 
    } 
  
    for (int i = 0; i < n; i++) 
        if (array[i].processID == min.processID) { 
            array[i] = min; 
            break; 
        } 
} 
  
// This function is responsible for 
// managing the entire execution of the 
// processes as they arrive in the CPU 
// according to their arrival time. 
void priority(Process array[], int n) 
{ 
    sort(array, array + n, compare); 
  
    int totalwaitingtime = 0, totalbursttime = 0, 
        totalturnaroundtime = 0, i, insertedprocess = 0, 
        heapsize = 0, currentTime = array[0].arrivalTime, 
        totalresponsetime = 0; 
  
    Process Heap[4 * n]; 
  
    // Calculating the total burst time 
    // of the processes 
    for (int i = 0; i < n; i++) { 
        totalbursttime += array[i].burstTime; 
        array[i].tempburstTime = array[i].burstTime; 
    } 
  
    // Inserting the processes in Heap 
    // according to arrival time 
    do { 
        if (insertedprocess != n) { 
            for (i = 0; i < n; i++) { 
                if (array[i].arrivalTime == currentTime) { 
                    ++insertedprocess; 
                    array[i].intime = -1; 
                    array[i].responsetime = -1; 
                    insert(Heap, array[i], &heapsize, ?tTime); 
                } 
            } 
        } 
        scheduling(Heap, array, n, &heapsize, ?tTime); 
        ++currentTime; 
        if (heapsize == 0 && insertedprocess == n) 
            break; 
    } while (1); 
  
    for (int i = 0; i < n; i++) { 
        totalresponsetime += array[i].responsetime; 
        totalwaitingtime += (array[i].outtime - array[i].intime - 
                                         array[i].tempburstTime); 
        totalbursttime += array[i].burstTime; 
    } 
    printf("Average waiting time = %f\n", 
           ((float)totalwaitingtime / (float)n)); 
    printf("Average response time =%f\n", 
           ((float)totalresponsetime / (float)n)); 
    printf("Average turn around time = %f\n", 
           ((float)(totalwaitingtime + totalbursttime) / (float)n)); 
} 
  
// Driver code 
int main() 
{ 
    int n, i; 
    Process a[5]; 
    a[0].processID = 1; 
    a[0].arrivalTime = 4; 
    a[0].priority = 2; 
    a[0].burstTime = 6;
	 
    a[1].processID = 4; 
    a[1].arrivalTime = 5; 
    a[1].priority = 1; 
    a[1].burstTime = 3; 
    
    a[2].processID = 2; 
    a[2].arrivalTime = 5; 
    a[2].priority = 3; 
    a[2].burstTime = 1; 
    
    a[3].processID = 3; 
    a[3].arrivalTime = 1; 
    a[3].priority = 4; 
    a[3].burstTime = 2; 
    
    a[4].processID = 5; 
    a[4].arrivalTime = 3; 
    a[4].priority = 5; 
    a[4].burstTime = 4; 
    priority(a, 5); 
    return 0; 
} 
*/ 

// C++ implementation for Priority Scheduling with  
//Different Arrival Time priority scheduling 
/*1. sort the processes according to arrival time  
2. if arrival time is same the acc to priority 
3. apply fcfs 
*/
  
#include <bits/stdc++.h> 
  
using namespace std; 
  
#define totalprocess 5 
  
// Making a struct to hold the given input  
  
struct process 
{ 
int at,bt,pr,pno; 
}; 
  
process proc[50]; 
  
/* 
Writing comparator function to sort according to priority if  
arrival time is same  
*/
  
bool comp(process a,process b) 
{ 
if(a.at == b.at) 
{ 
return a.pr<b.pr; 
} 
else
{ 
    return a.at<b.at; 
} 
} 
  
// Using FCFS Algorithm to find Waiting time 
void get_wt_time(int wt[]) 
{ 
// declaring service array that stores cumulative burst time  
int service[50]; 
  
// Initilising initial elements of the arrays 
service[0] = proc[0].at; 
wt[0]=0; 
  
  
for(int i=1;i<totalprocess;i++) 
{ 
service[i]=proc[i-1].bt+service[i-1]; 
  
wt[i]=service[i]-proc[i].at; 
  
// If waiting time is negative, change it into zero 
      
    if(wt[i]<0) 
    { 
    wt[i]=0; 
    } 
} 
  
} 
  
void get_tat_time(int tat[],int wt[]) 
{ 
// Filling turnaroundtime array 
  
for(int i=0;i<totalprocess;i++) 
{ 
    tat[i]=proc[i].bt+wt[i]; 
} 
      
} 
  
void findgc() 
{ 
//Declare waiting time and turnaround time array 
int wt[50],tat[50]; 
  
double wavg=0,tavg=0; 
  
// Function call to find waiting time array 
get_wt_time(wt); 
//Function call to find turnaround time 
get_tat_time(tat,wt); 
      
int stime[50],ctime[50]; 
  
stime[0] = proc[0].at; 
ctime[0]=stime[0]+tat[0]; 
  
// calculating starting and ending time 
for(int i=1;i<totalprocess;i++) 
    { 
        stime[i]=ctime[i-1]; 
        ctime[i]=stime[i]+tat[i]-wt[i]; 
    } 
      
cout<<"Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time"<<endl; 
      
    // display the process details 
      
for(int i=0;i<totalprocess;i++) 
    { 
        wavg += wt[i]; 
        tavg += tat[i]; 
          
        cout<<proc[i].pno<<"\t\t"<< 
            stime[i]<<"\t\t"<<ctime[i]<<"\t\t"<< 
            tat[i]<<"\t\t\t"<<wt[i]<<endl; 
    } 
      
        // display the average waiting time 
        //and average turn around time 
      
    cout<<"Average waiting time is : "; 
    cout<<wavg/(float)totalprocess<<endl; 
    cout<<"average turnaround time : "; 
    cout<<tavg/(float)totalprocess<<endl; 
  
} 
  
int main() 
{ 
int arrivaltime[] = { 4, 5, 1, 5, 3 }; 
int bursttime[] = { 2, 3, 4, 1, 5 }; 
int priority[] = { 6, 1, 2, 3, 4 }; 
      
for(int i=0;i<totalprocess;i++) 
{ 
    proc[i].at=arrivaltime[i]; 
    proc[i].bt=bursttime[i]; 
    proc[i].pr=priority[i]; 
    proc[i].pno=i+1; 
    }  
      
    //Using inbuilt sort function 
      
    sort(proc,proc+totalprocess,comp); 
      
    //Calling function findgc for finding Gantt Chart 
      
    findgc();  
  
    return 0; 
} 
