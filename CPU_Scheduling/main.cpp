# include <iostream>
# include <stdio.h>
# include <vector>
# include <ctype.h>
# include <string> 
# include <cstring>
# include <fstream>
# include <thread>
# include <time.h>
# include <queue>

#define MAX 32767;

using namespace std;

struct aProcess {
  int id;
  int cpuBurst;
  int arrivalTime;
  int priority;
  int turnAround;
  int waiting;
};

struct outData {
  int id;
  int turnAround;
  int waiting;
};

string whatMission ;
int timeSlice = 0 ;
vector <aProcess> processes;
vector <outData> fcfsOut;
vector <char> fcfsGantt;

vector <outData> rrOut;
vector <char> rrGantt;

vector <outData> npsjfOut;
vector <char> npsjfGantt;

vector <outData> psjfOut;
vector <char> psjfGantt;

vector <outData> ppOut;
vector <char> ppGantt;

bool getFile( string fileName ) {
  ifstream fin;
  char ch;
  aProcess a;
  string stay ;
  string stay2;
  string TC;
  int line = 0;
  //string stay2;
  bool stop = false; 
  vector <string> data;
  
  fin.open(fileName);

  if (!fin) {
    return false;
	//cout << "檔案無法開啟或不存在!\n";
  } // if
  else {
	getline( fin,stay );
	for ( int i = 0 ; i < stay.length() ; i++ ) {
	  if ( stay[i] != ' ' ) {
	      if ( i == 0 ) {
	        whatMission = whatMission + stay[i];
		  } // if
		  
		  if ( i > 0 ) {
	        TC = TC + stay[i];
	        timeSlice = stoi(TC);
		  } // if
	  } // if
	} // for
	
	//cout << whatMission << "###1\n" << timeSlice << "###2\n";
	getline( fin,stay ); // 把欄目讀掉 
	
	while ( fin.peek() != EOF && !stop ) {
	  getline( fin,stay );
	  for ( int i = 0, j = 1 ; i < stay.length() ; i++ ) {
	  	if ( stay[i] != '\t' && stay[i] != ' ' ) {
	  	  stay2 = stay2 + stay[i];
	  	  if ( j == 1 ) {
	  	  	while ( stay[i+1] != ' ' && stay[i+1] != '\t' ) {
	  	  		stay2 = stay2 + stay[i+1];
	  	  		i++;
			} // while
			
		    a.id = stoi( stay2 );
		    //cout << a.id << " i\n";
		    stay2 = "\0"; 
		    j++; 
		  }  // if
		  else if ( j == 2 ) {
		  	while ( stay[i+1] != ' ' && stay[i+1] != '\t' ) {
	  	  		stay2 = stay2 + stay[i+1];
	  	  		i++;
			} // while
			
		    a.cpuBurst = stoi( stay2 );
		    //cout << a.cpuBurst << " c\n";
		    stay2 = "\0";
		    j++; 
		  } // if
		  else if ( j == 3 ) {
		  	while ( stay[i+1] != ' ' && stay[i+1] != '\t' ) {
	  	  		stay2 = stay2 + stay[i+1];
	  	  		i++;
			} // while
			
		    a.arrivalTime = stoi( stay2 );
		    //cout << a.arrivalTime << " a\n";
		    stay2 = "\0";
		    j++; 
		  } // if
		  else if ( j == 4 ) {
		  	while ( i <= stay.length() - 1 && stay[i+1] != ' ' && stay[i+1] != '\t' ) {
	  	  		stay2 = stay2 + stay[i+1];
	  	  		i++;
			} // while
			
		    a.priority = stoi( stay2 );
		    //cout << a.priority << " p\n";
		    stay2 = "\0";
		    j++; 
		  } // if
	    } // if
	  } // for
	  
	  processes.push_back( a ) ;
	} // while
	
	return true;
  } // else 

} // getFile ()

void sortProcesses( vector <aProcess> & sProcesses ) {
	aProcess stay;
	
	for ( int i = 0 ; i < processes.size(); i++ ) {
	  stay.id =  processes[i].id;
	  stay.cpuBurst = processes[i].cpuBurst;
	  stay.arrivalTime = processes[i].arrivalTime;
	  stay.priority = processes[i].priority;
	  sProcesses.push_back( stay );
	} // for 
	
	for (int i = 0; i < sProcesses.size() ; i++) {
	  for (int j = 0; j < sProcesses.size() ; j++) {
	    if ( sProcesses[i].arrivalTime < sProcesses[j].arrivalTime ) {
		  stay.id =  sProcesses[i].id;
	      stay.cpuBurst = sProcesses[i].cpuBurst;
    	  stay.arrivalTime = sProcesses[i].arrivalTime;
	      stay.priority = sProcesses[i].priority;
	      
	      sProcesses[i].id =  sProcesses[j].id;
	      sProcesses[i].cpuBurst = sProcesses[j].cpuBurst;
    	  sProcesses[i].arrivalTime = sProcesses[j].arrivalTime;
	      sProcesses[i].priority = sProcesses[j].priority;
	      
	      sProcesses[j].id = stay.id;
	      sProcesses[j].cpuBurst = stay.cpuBurst;
    	  sProcesses[j].arrivalTime = stay.arrivalTime;
	      sProcesses[j].priority = stay.priority;
		} // if
		else if ( sProcesses[i].arrivalTime == sProcesses[j].arrivalTime ) {
		  if ( sProcesses[i].id < sProcesses[j].id ) {
		    stay.id =  sProcesses[i].id;
	        stay.cpuBurst = sProcesses[i].cpuBurst;
    	    stay.arrivalTime = sProcesses[i].arrivalTime;
	        stay.priority = sProcesses[i].priority;
	      
	        sProcesses[i].id =  sProcesses[j].id;
	        sProcesses[i].cpuBurst = sProcesses[j].cpuBurst;
    	    sProcesses[i].arrivalTime = sProcesses[j].arrivalTime;
	        sProcesses[i].priority = sProcesses[j].priority;
	      
	        sProcesses[j].id = stay.id;
	        sProcesses[j].cpuBurst = stay.cpuBurst;
    	    sProcesses[j].arrivalTime = stay.arrivalTime;
	        sProcesses[j].priority = stay.priority;        
		  } // if 
		}//else
	  } // for
	} // for
} // sortProcesses()

void sortOutProcesses( vector <aProcess> & sProcesses ) {
	aProcess stay;
	
	for (int i = 0; i < sProcesses.size() ; i++) {
	  for (int j = 0; j < sProcesses.size() ; j++) {
	    if ( sProcesses[i].id < sProcesses[j].id ) {
		  stay.id = sProcesses[i].id;
	      stay.cpuBurst = sProcesses[i].cpuBurst;
    	  stay.arrivalTime = sProcesses[i].arrivalTime;
	      stay.priority = sProcesses[i].priority;
	      stay.waiting = sProcesses[i].waiting;
	      stay.turnAround = sProcesses[i].turnAround;
	      
	      sProcesses[i].id =  sProcesses[j].id;
	      sProcesses[i].cpuBurst = sProcesses[j].cpuBurst;
    	  sProcesses[i].arrivalTime = sProcesses[j].arrivalTime;
	      sProcesses[i].priority = sProcesses[j].priority;
	      sProcesses[i].waiting = sProcesses[j].waiting;
	      sProcesses[i].turnAround = sProcesses[j].turnAround;
	      
	      sProcesses[j].id = stay.id;
	      sProcesses[j].cpuBurst = stay.cpuBurst;
    	  sProcesses[j].arrivalTime = stay.arrivalTime;
	      sProcesses[j].priority = stay.priority;
	      sProcesses[j].waiting = stay.waiting;
	      sProcesses[j].turnAround = stay.turnAround;
	      
		} // if
	  } // for
	} // for
} // sortProcesses()

void FCFS() {
  vector <aProcess> sProcesses;
  aProcess stay;
  bool pGet;  // Get a process
  int nowTime = 0;
  char g = '\0';

  sortProcesses( sProcesses );
  // 排序，把做的順序找出來

  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
    if ( nowTime == 0 && i == 0 ) { // 第一個 
      sProcesses[i].waiting = 0;
      for ( int j = 0 ; j < sProcesses[i].arrivalTime ; j ++ ) {
      	fcfsGantt.push_back('-');
	  } // for 
	  
      nowTime =  sProcesses[i].arrivalTime;
      nowTime = nowTime + sProcesses[i].cpuBurst ;
      sProcesses[i].turnAround = nowTime - sProcesses[i].arrivalTime;
      for ( int j = 0 ; j < sProcesses[i].cpuBurst ; j ++ ) {
        if ( sProcesses[i].id > 9 ) {
          g = 'A' + sProcesses[i].id - 10;
          fcfsGantt.push_back( g );
		} // if
		else {
		  g = '0' + sProcesses[i].id ;
          fcfsGantt.push_back( g );
	    } // else   	  
	  } // for
    } // if 
    else {
      if ( nowTime < sProcesses[i].arrivalTime ) {
      	int a = sProcesses[i].arrivalTime - nowTime;
      	for ( int j = 0 ; j < a ; j ++ ) {
      	  fcfsGantt.push_back('-');
	    } // for
	    
	    nowTime = sProcesses[i].arrivalTime;
	    sProcesses[i].waiting = nowTime - sProcesses[i].arrivalTime; 
        nowTime = nowTime + sProcesses[i].cpuBurst ;
        sProcesses[i].turnAround = nowTime - sProcesses[i].arrivalTime;
        
        for ( int j = 0 ; j < sProcesses[i].cpuBurst ; j++ ) {
          if ( sProcesses[i].id > 9 ) {
            g = 'A' + sProcesses[i].id - 10;
            fcfsGantt.push_back( g );
		  } // if
		  else {
		    g = '0' + sProcesses[i].id ;
            fcfsGantt.push_back( g );
		  } // else   	  
	    } // for
	  } // if
	  else {
	  	sProcesses[i].waiting = nowTime - sProcesses[i].arrivalTime; 
        nowTime = nowTime + sProcesses[i].cpuBurst ;
        sProcesses[i].turnAround = nowTime - sProcesses[i].arrivalTime;
        
        for ( int j = 0 ; j < sProcesses[i].cpuBurst ; j++ ) {
          if ( sProcesses[i].id > 9 ) {
            g = 'A' + sProcesses[i].id - 10;
            fcfsGantt.push_back( g );
		  } // if
		  else {
		    g = '0' + sProcesses[i].id ;
            fcfsGantt.push_back( g );
		  } // else   	  
	    } // for
	  } // else
    } // else
  } // for  

  sortOutProcesses( sProcesses );
  outData stay2; 
  
  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
  	stay2.id =  sProcesses[i].id;
  	stay2.waiting = sProcesses[i].waiting;
  	stay2.turnAround = sProcesses[i].turnAround;
  	fcfsOut.push_back( stay2 );
  } // for
} // FCFS

void NPSJF () {
  vector <aProcess> sProcesses;
  aProcess stay;
  bool pGet;  // Get a process
  bool allCome = false;
  int nowTime = 0;
  char g = '\0';
  	
  sortProcesses( sProcesses );
  
  bool done[sProcesses.size()] = {0};
  
  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
    int j = 0, toDo = 0, low =INT_MAX;
    
	while ( nowTime >= sProcesses[j].arrivalTime && !allCome ) {
	  if ( j == sProcesses.size() - 1 ) 
	    allCome = true;
	  if ( j < sProcesses.size() ) 
	    j++;
	} // while
   	
   	if ( allCome ) j = sProcesses.size() - 1;
   	else j = j - 1;
   	// J存現在那些到了 ,allCome亮了表示都到了 
   	
   	for ( int k = 0 ; k <= j ; k++ ) {
   	  if ( !done[k] && low > sProcesses[k].cpuBurst ) {
   	  	low = sProcesses[k].cpuBurst;
   	  	toDo = k;
      } // if
	} // for
   	
   	done[toDo] = true;
   	
   	if ( nowTime < sProcesses[toDo].arrivalTime ) {
   	  int a = sProcesses[i].arrivalTime - nowTime;
      for ( int j = 0 ; j < a ; j ++ ) {
        npsjfGantt.push_back('-');
	  } // for
	  
	  sProcesses[toDo].waiting = nowTime - sProcesses[toDo].arrivalTime; 
 	  if ( sProcesses[toDo].waiting < 0 )  sProcesses[toDo].waiting = 0; 
      nowTime = sProcesses[toDo].arrivalTime + sProcesses[toDo].cpuBurst ; 
      sProcesses[toDo].turnAround = nowTime - sProcesses[toDo].arrivalTime;
      
      for ( int j = 0 ; j < sProcesses[i].cpuBurst ; j++ ) {
        if ( sProcesses[i].id > 9 ) {
          g = 'A' + sProcesses[i].id - 10;
          npsjfGantt.push_back( g );
	    } // if
	    else {
	      g = '0' + sProcesses[i].id ;
          npsjfGantt.push_back( g );
	    } // else   	  
  	  } // for
    } // if 
    else {
      sProcesses[toDo].waiting = nowTime - sProcesses[toDo].arrivalTime; 
 	  if ( sProcesses[toDo].waiting < 0 )  sProcesses[toDo].waiting = 0; 
      nowTime = nowTime + sProcesses[toDo].cpuBurst ; 
      sProcesses[toDo].turnAround = nowTime - sProcesses[toDo].arrivalTime;
      
      for ( int j = 0 ; j < sProcesses[i].cpuBurst ; j++ ) {
        if ( sProcesses[i].id > 9 ) {
          g = 'A' + sProcesses[i].id - 10;
          npsjfGantt.push_back( g );
	    } // if
	    else {
	      g = '0' + sProcesses[i].id ;
          npsjfGantt.push_back( g );
	    } // else   	  
	  } // for
	} // else
  } // for
  
  sortOutProcesses( sProcesses );
  outData stay2; 
  
  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
  	stay2.id =  sProcesses[i].id;
  	stay2.waiting = sProcesses[i].waiting;
  	stay2.turnAround = sProcesses[i].turnAround;
  	npsjfOut.push_back( stay2 );
  } // for
  
} // NPSJF

void PSJF () {
  vector <aProcess> sProcesses;
  aProcess stay;
  bool pGet;  // Get a process
  bool allCome = false;
  char g = '\0';
  
  sortProcesses( sProcesses );

  int bT[sProcesses.size()] ; // Burst Time 暫存
  bool check = false; // 找到最短的 
  int complete = 0, nowTime = 0, low = INT_MAX;
  int shortPro = 0; 

  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
  	bT[i] = sProcesses[i].cpuBurst; // 暫存處理時間 
  } // for 
  
  while ( complete < sProcesses.size() ) {
  	for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
  	  if ( nowTime >= sProcesses[i].arrivalTime && bT[i] < low && bT[i] > 0 ) {
  	  	low = bT[i]; // 現在最短的 
  	  	shortPro = i;
  	  	check = true; 
	  } // if
	} // for
	
	if ( !check ) {
	  nowTime++;
	  psjfGantt.push_back('-');
	} // if
	else {
      bT[shortPro] = bT[shortPro] - 1; // 做了一秒 
      low = bT[shortPro];
      
      if ( sProcesses[shortPro].id > 9 ) {
        g = 'A' + sProcesses[shortPro].id - 10;
        psjfGantt.push_back( g );
	  } // if
	  else {
	    g = '0' + sProcesses[shortPro].id ;
        psjfGantt.push_back( g );
	  } // else   	  
      
      if ( low == 0 ) low = INT_MAX;
      if ( bT[shortPro] == 0 ) {
        complete++; // 做完一個 
        check = false;
        
        sProcesses[shortPro].waiting = nowTime + 1 - sProcesses[shortPro].cpuBurst - sProcesses[shortPro].arrivalTime;
      	if ( sProcesses[shortPro].waiting < 0 ) {
      	  sProcesses[shortPro].waiting = 0;
	    } // if
	  } // if
      
	  nowTime++;
	} // else
  } // while
  
  for (int i = 0; i < sProcesses.size() ; i++) {
  	sProcesses[i].turnAround = sProcesses[i].cpuBurst + sProcesses[i].waiting;
  } // for
  
  sortOutProcesses( sProcesses );
  outData stay2; 
  
  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
  	stay2.id =  sProcesses[i].id;
  	stay2.waiting = sProcesses[i].waiting;
  	stay2.turnAround = sProcesses[i].turnAround;
  	psjfOut.push_back( stay2 );
  } // for
} // PSJF()

void RR() {
  vector <aProcess> sProcesses;
  aProcess stay;
  char g = '\0';
  
  sortProcesses( sProcesses ); 
  
  int complete = 0, j = 0;
  int bT[ sProcesses.size() ] ;
  int nowTime = 0, doNow = 0,  lastSec = 0;
  vector <int> WQ;
  bool inQ[sProcesses.size()] = {false};
  
  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
  	bT[i] = sProcesses[i].cpuBurst;
  } // for
  
  while( complete < sProcesses.size() ) { 
    doNow = INT_MAX;
    
  	if ( !WQ.empty() ) {
	  doNow = WQ[0];
	  WQ.erase( WQ.begin() );
	} // if
	
	if ( doNow != INT_MAX ) {
	  for ( int i = 0 ; i < timeSlice ; i++ ) {
	  	
	  	bT[doNow]--;
	    nowTime++; 
	  	
	  	for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
          if ( sProcesses[i].arrivalTime == nowTime && bT[i] > 0 ) {
      	    if ( !inQ[i] ) { // 沒在裡面 
      	      WQ.push_back( i );
      	      inQ[i] = true;
 		    } // if 
	      } // if
	    } // for
	  	
	  	if ( sProcesses[doNow].id > 9 ) {
          g = 'A' + sProcesses[doNow].id - 10;
          rrGantt.push_back( g );
	    } // if
	    else {
	      g = '0' + sProcesses[doNow].id ;
          rrGantt.push_back( g );
	    } // else   	  
	  	
	    if ( i < timeSlice && bT[doNow] == 0 ) {
	      i = timeSlice;
		} // if 
	  } // for
	  
	  inQ[doNow] = false;
	  lastSec = doNow;	  
	} // if
	else {
	  rrGantt.push_back('-');
	  nowTime++;
	} // else
	
	if ( doNow != INT_MAX && bT[doNow] == 0 ) {
	  sProcesses[doNow].waiting = nowTime - sProcesses[doNow].cpuBurst - sProcesses[doNow].arrivalTime;
	  sProcesses[doNow].turnAround = sProcesses[doNow].cpuBurst + sProcesses[doNow].waiting;
	  complete++;
	} // if
	
    for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
      if ( sProcesses[i].arrivalTime == nowTime && bT[i] > 0 ) {
      	if ( !inQ[i] ) { // 沒在裡面 
      	  WQ.push_back( i );
      	  inQ[i] = true;
 		} // if 
	  } // if
	} // for
	
	for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
      if ( sProcesses[i].arrivalTime < nowTime && bT[i] > 0 ) {
      	if ( !inQ[i] ) { // 沒在裡面 
      	  WQ.push_back( i );
      	  inQ[i] = true;
 		} // if 
	  } // if
	} // for
	
  } // while
  
  sortOutProcesses( sProcesses );
  outData stay2; 
  
  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
  	stay2.id =  sProcesses[i].id;
  	stay2.waiting = sProcesses[i].waiting;
  	stay2.turnAround = sProcesses[i].turnAround;
  	rrOut.push_back( stay2 );
  } // for
  
} // RR()

void PP () {
  vector <aProcess> sProcesses;
  aProcess stay;
  char g = '\0';
  
  sortProcesses( sProcesses ); // 排好 
  
  int bT[sProcesses.size()] ;
  int n = sProcesses.size();
  int nowTime = 0, complete = 0 ;
  int sT = 0, lastSec = 0;
  bool did[sProcesses.size()] = {false};
  
  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
  	bT[i] = sProcesses[i].cpuBurst; // 暫存處理時間 
  } // for
  
  for ( nowTime = 0 ; complete < n ; nowTime++ ) {
  	int low = INT_MAX, PrePro = INT_MAX;
    for ( int i = 0 ; i < n ; i++ ) {
      if( sProcesses[i].arrivalTime <= nowTime && sProcesses[i].priority < low && bT[i] > 0 ) {
      	low = sProcesses[i].priority;
        PrePro = i;
	  } // if
	  else if ( sProcesses[i].arrivalTime <= nowTime && sProcesses[i].priority == low && bT[i] > 0 ) {
	  	
	  	if ( did[PrePro] && !did[i] && lastSec != PrePro ) {
	  	  low = sProcesses[i].priority;
	  	  PrePro = i;
	    } // if
	    
		if ( did[i] && !did[PrePro] && lastSec != i ) {
	      low = low;
	  	  PrePro = PrePro;
		} // if
		
		if ( did[i] && did[PrePro] ) {
		  if ( sProcesses[i].arrivalTime == sProcesses[PrePro].arrivalTime ) {
		  	if ( i < PrePro ) {
		  	  low = sProcesses[i].priority;
	  	      PrePro = i;
			} // if 
			else {
			  low = low;
	  	      PrePro = PrePro;
			} // else
		  } // if
		  else {
		  	if ( sProcesses[i].arrivalTime < sProcesses[PrePro].arrivalTime  ) {
		  	  if ( lastSec == PrePro ) {
			  	low = low;
	  	        PrePro = PrePro;
			  } // if
			  else {
			  	low = sProcesses[i].priority;
	  	        PrePro = i;			  
			  } // else			  
			} // if
			else if ( sProcesses[i].arrivalTime > sProcesses[PrePro].arrivalTime ) {
			  if ( lastSec == i ) {
			  	low = sProcesses[i].priority;
	  	        PrePro = i;
			  } // if
			  else {
			  	low = low;
	  	        PrePro = PrePro;
			  } // else			  
			} // else
		  } // else
		} // if
				
		if ( !did[PrePro] && !did[i] ) {
		  if ( sProcesses[i].arrivalTime == sProcesses[PrePro].arrivalTime ) {
		  	if ( i < PrePro ) {
		  	  low = sProcesses[i].priority;
	  	      PrePro = i;
			} // if 
			else {
			  low = low;
	  	      PrePro = PrePro;
			} // else
		  } // if
		  else {
		  	if ( sProcesses[i].arrivalTime < sProcesses[PrePro].arrivalTime ) {
		  	  low = sProcesses[i].priority;
	  	      PrePro = i;
			} // if
			else {
			  low = low;
	  	      PrePro = PrePro;
			} // else
		  } // else
		} // if
	  } // else if
	} // for
	
	if ( PrePro != INT_MAX ) {
	  //cout << sProcesses[PrePro].id << " " ;
	  bT[PrePro]--;
	  did[PrePro] = true;
	  lastSec = PrePro;
	  
	  if ( sProcesses[PrePro].id > 9 ) {
        g = 'A' + sProcesses[PrePro].id - 10;
        ppGantt.push_back( g );
	  } // if
	  else {
	    g = '0' + sProcesses[PrePro].id ;
        ppGantt.push_back( g );
	  } // else   	  
	  
	  if( bT[PrePro] == 0 ) {
        complete++;
        sT = nowTime + 1;
        sProcesses[PrePro].waiting = sT -  sProcesses[PrePro].arrivalTime - sProcesses[PrePro].cpuBurst;
        sProcesses[PrePro].turnAround = sT - sProcesses[PrePro].arrivalTime;
      } // if
	} // if 
	else {
	  g = '-';
      ppGantt.push_back( g );
	} // else
	
  } // for

  sortOutProcesses( sProcesses );
  outData stay2; 
  
  for ( int i = 0 ; i < sProcesses.size() ; i++ ) {
  	stay2.id =  sProcesses[i].id;
  	stay2.waiting = sProcesses[i].waiting;
  	stay2.turnAround = sProcesses[i].turnAround;
  	ppOut.push_back( stay2 );
  } // for
  
} // pp()

void writeFile( string fileName, vector <outData> out, vector <char> gantt, string whatMission ) {
  ofstream fout;
  string outFileName = "output";
  char a;
  
  a = fileName[fileName.size() - 5];
  cout << a <<"\n";
  if ( a >= '0' && a <= '9' ) {
  	outFileName = outFileName + a;
  	outFileName = outFileName + ".txt";
  } // if
  else outFileName = outFileName + ".txt";
  
  cout << "Output File Name : " << outFileName << "\n";
  fout.open( outFileName );
  
  if ( whatMission == "1" ) fout << "==    FCFS==\n";
  if ( whatMission == "2" ) fout << "==      RR==\n";
  if ( whatMission == "3" ) fout << "==    PSJF==\n";
  if ( whatMission == "4" ) fout << "==Non-PSJF==\n";
  if ( whatMission == "5" ) fout << "==      PP==\n";
  
  if ( whatMission == "1" ) cout << "==    FCFS==\n";
  if ( whatMission == "2" ) cout << "==      RR==\n";
  if ( whatMission == "3" ) cout << "==    PSJF==\n";
  if ( whatMission == "4" ) cout << "==Non-PSJF==\n";
  if ( whatMission == "5" ) cout << "==      PP==\n";
  
  for ( int i = 0 ; i < gantt.size() ; i++ ) {
  	fout << gantt[i];
  } // for
  
  fout << "\n";
  for ( int i = 0 ; i < out.size() ; i++ ) {
  	fout << out[i].id << "\t"
         << out[i].waiting << "\t" 
	     << out[i].turnAround << "\n";
	     
	cout << out[i].id << "\t"
         << out[i].waiting << "\t" 
	     << out[i].turnAround << "\n";
  } // for
  
} // writeFile

void writeFileSix( string fileName ) {
  ofstream fout;
  string outFileName = "output";
  char a;
  
  a = fileName[fileName.size() - 5];
  cout << a <<"\n";
  if ( a >= '0' && a <= '9' ) {
  	outFileName = outFileName + a;
  	outFileName = outFileName + ".txt";
  } // if
  else outFileName = outFileName + ".txt";
  
  cout << "Output File Name : " << outFileName << "\n";
  fout.open( outFileName );
  
  fout << "==    FCFS==\n";
  for ( int i = 0 ; i < fcfsGantt.size() ; i++ ) {
  	fout << fcfsGantt[i];
  	cout << fcfsGantt[i];
  } // for
  
  fout << "\n==      RR==\n";
  cout << "\n==      RR==\n";
  for ( int i = 0 ; i < rrGantt.size() ; i++ ) {
  	fout << rrGantt[i];
  	cout << rrGantt[i];
  } // for
  
  fout << "\n==    PSJF==\n";
  cout << "\n==    PSJF==\n";
  for ( int i = 0 ; i < psjfGantt.size() ; i++ ) {
  	fout <<psjfGantt[i];
  	cout <<psjfGantt[i];
  } // for
  
  fout << "\n==Non-PSJF==\n";
  cout << "\n==Non-PSJF==\n";
  for ( int i = 0 ; i < npsjfGantt.size() ; i++ ) {
  	fout << npsjfGantt[i];
    cout << npsjfGantt[i];
  } // for
  
  fout << "\n==      PP==\n";
  cout << "\n==      PP==\n";
  for ( int i = 0 ; i < ppGantt.size() ; i++ ) {
  	fout << ppGantt[i];
  	cout << ppGantt[i];
  } // for
  
  fout << "\n===========================================================\n\n";
  cout << "\n===========================================================\n\n";
  
  fout << "Waiting Time\n";
  fout << "ID      FCFS    RR      PSJF    NPSJF   Priority\n";
  fout << "===========================================================\n";
  
  cout << "Waiting Time\n";
  cout << "ID      FCFS    RR      PSJF    NPSJF   Priority\n";
  cout << "===========================================================\n";
  
  for ( int i = 0 ; i < fcfsOut.size() ; i++ ) {
  	fout << i << "\t"
	     << fcfsOut[i].waiting << "\t"
         << rrOut[i].waiting << "\t" 
         << psjfOut[i].waiting << "\t" 
         << npsjfOut[i].waiting << "\t" 
	     << ppOut[i].waiting << "\n";
	     
	cout << i << "\t"
	     << fcfsOut[i].waiting << "\t"
         << rrOut[i].waiting << "\t" 
         << psjfOut[i].waiting << "\t" 
         << npsjfOut[i].waiting << "\t" 
	     << ppOut[i].waiting << "\n";
  } // for
  
  fout << "===========================================================\n\n";
  
  fout << "Turnaround Time\n";
  fout << "ID      FCFS    RR      PSJF    NPSJF   Priority\n";
  fout << "===========================================================\n";
  
  for ( int i = 0 ; i < fcfsOut.size() ; i++ ) {
  	fout << i << "\t"
	     << fcfsOut[i].turnAround << "\t"
         << rrOut[i].turnAround << "\t" 
         << psjfOut[i].turnAround << "\t" 
         << npsjfOut[i].turnAround << "\t" 
	     << ppOut[i].turnAround << "\n";
	     
	cout << i << "\t"
	     << fcfsOut[i].turnAround << "\t"
         << rrOut[i].turnAround << "\t" 
         << psjfOut[i].turnAround << "\t" 
         << npsjfOut[i].turnAround << "\t" 
	     << ppOut[i].turnAround << "\n";
  } // for
  
  fout << "===========================================================\n\n";
  cout << "===========================================================\n\n";
} // writeFile

int main() {
	
  string fileName;
  bool leave = false;
  bool hasFile;
	
  while ( !leave ) {
    cout << "FileName: ";
    cin >> fileName;
  
    if (fileName == "0") {
      leave = true;
	} // if
	else {
	  hasFile = getFile(fileName);
	} // else
		
	if (!hasFile && !leave ) {
	  cout << "檔案無法開啟或不存在!\n";
	} // if
	else {
	  if ( whatMission == "1" ){
	    FCFS();
	    cout << "==    FCFS==\n";
  
        for ( int i = 0 ; i < fcfsGantt.size() ; i++ ) {
    	  cout << fcfsGantt[i];
  		} // for 
  
  		cout << "\n===========================================================\n";
   		cout << "ID      Waiting Time      Turnaround Time\n"; 
  
  		for ( int i = 0 ; i < fcfsOut.size() ; i++ ) {
  		  cout << fcfsOut[i].id << "      "
     	  << fcfsOut[i].waiting << "      " 
	      << fcfsOut[i].turnAround << " \n";
		} // for
		
		writeFile( fileName, fcfsOut, fcfsGantt, whatMission );
      } // if
	  else if ( whatMission == "2" ) {
	  	RR();  	
	  	cout << "==      RR==\n";
  
        for ( int i = 0 ; i < rrGantt.size() ; i++ ) {
  		  cout << rrGantt[i];
		} // for 
  
  		cout << "\n===========================================================\n";
   		cout << "ID      Waiting Time      Turnaround Time\n"; 
  
  		for ( int i = 0 ; i < rrOut.size() ; i++ ) {
  		  cout << rrOut[i].id << "      "
	      << rrOut[i].waiting << "      " 
		  << rrOut[i].turnAround << " \n";
  	    } // for
  	    
  	    writeFile( fileName, rrOut, rrGantt, whatMission );
	  } // else if 
	  else if ( whatMission == "3" ) {
	    PSJF();
	    cout << "==    PSJF==\n";
  
  		for ( int i = 0 ; i < psjfGantt.size() ; i++ ) {
          cout << psjfGantt[i];
  		} // for 
  
  		cout << "\n===========================================================\n";
  		cout << "ID      Waiting Time      Turnaround Time\n"; 
  
  		for ( int i = 0 ; i < psjfOut.size() ; i++ ) {
  		  cout << psjfOut[i].id << "      "
    		   << psjfOut[i].waiting << "      " 
  			   << psjfOut[i].turnAround << " \n";
		} // for
		
		writeFile( fileName, psjfOut, psjfGantt, whatMission );
	  } // else if 
	  else if ( whatMission == "4" ) {
	    NPSJF();
	    cout << "==Non-PSJF==\n";
 
		for ( int i = 0 ; i < npsjfGantt.size() ; i++ ) {
  	      cout << npsjfGantt[i];
		} // for 
  
		cout << "\n===========================================================\n";
		cout << "ID      Waiting Time      Turnaround Time\n"; 

		for ( int i = 0 ; i < npsjfOut.size() ; i++ ) {
		  cout << npsjfOut[i].id << "      "
   		       << npsjfOut[i].waiting << "      " 
	  		   << npsjfOut[i].turnAround << " \n";
  	    } // for
  	    
  	    writeFile( fileName, npsjfOut, npsjfGantt, whatMission );
	  } // else if 
	  else if ( whatMission == "5" ) {
	    PP();
	    cout << "==      PP==\n";
  
  		for ( int i = 0 ; i < ppGantt.size() ; i++ ) {
   	      cout << ppGantt[i];
  		} // for 
  
  		cout << "\n===========================================================\n";
  		cout << "ID      Waiting Time      Turnaround Time\n"; 
  
  		for ( int i = 0 ; i < ppOut.size() ; i++ ) {
  		  cout << ppOut[i].id << "      "
    		   << ppOut[i].waiting << "      " 
  			   << ppOut[i].turnAround << " \n";
	    } // for
	    
	    writeFile( fileName, ppOut, ppGantt, whatMission );
	  } // else if 
	  else if ( whatMission == "6" ) {
	  	FCFS();
	  	RR();
	    PSJF();
	    NPSJF();
	    PP();
	    
	    writeFileSix( fileName );
	  } // else if
	} // else
		
	vector <aProcess> ().swap(processes);
	vector <outData> ().swap(fcfsOut);
	vector <char> ().swap(fcfsGantt);
	
	vector <outData> ().swap(rrOut);
	vector <char> ().swap(rrGantt);
	
	vector <outData> ().swap(psjfOut);
	vector <char> ().swap(psjfGantt);
	
	vector <outData> ().swap(npsjfOut);
	vector <char> ().swap(npsjfGantt);
	
	vector <outData> ().swap(ppOut);
	vector <char> ().swap(ppGantt);
	
	whatMission = "\0" ;
    timeSlice = 0 ;
  } // while
	
  cout << "程式結束\n"; 
	return 0;
}
