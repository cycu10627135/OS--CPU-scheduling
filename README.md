# **CPU-scheduling**
寫一個程式可以自檔案輸入各個Process之編號、CPU Burst、Arrival Time、及Priority，並依這些資訊模擬FCFS、RR、Preemptive SJF、Non-Preemptive SJF、Priority等CPU Scheduling。本題必須繪出Gantt Chart，計算每個Process之Turnaround Time及Waiting Time。  
  
1. FCFS (First Come First Serve)  
   * 依arrival time先後次序處理。  
   * 若arrival time相同時, 則依ProcessID由小至大依序處理。
2. RR (Round Robin)  
   * 先依arrival time先後次序處理,時候未到的Process不能Run。  
   * 若arrival time相同時,則依ProcessID由小至大依序處理。  
   * Time out時, 若有新來的Process,則讓新來的Process排在前面。  
   * 某個ProcessTime slice未用完就結束時,必須讓下一個Process執行。  
3. PSJF (Preemptive Shortest Job First)  
   * 某個ProcessTime slice未用完就結束時,必須讓下一個Process執行。  
   * 若剩餘的CPU Burst相同,讓沒有用過CPU的先使用,無法分別時則依arrival time小的先處理。  
   * 若剩餘CPU Burst相同且arrival time相同,則依ProcessID由小至大依序處理。  

4. NSJF (Non-preemptive Shortest Job First)  
   * 由CPU Burst最小的Process先處。  
   * 若CPU Burst最少的Process不只一個,則依arrival time小的先處理。  
   * 若CPU Burst及arrival time相同,則依ProcessID由小至大依序處理。  
5. PP (Preemptive Priority)
   * Priority number小的代表Priority大。  
   * 依Priority由大致小依序處理。  
   * 若Priority相同,讓沒有用過CPU的先使用,無法分別時則依arrival time小的先處理。  
   * 若Priority及arrival time均相同,則依ProcessID由小至大依序處理。  
  
計算Turn around time及Waiting time、並按照結果繪製Gantt char。  
