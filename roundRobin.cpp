#include <bits/stdc++.h>
using namespace std;

struct Process {
    string pname;
    int arrival;
    int burst;
    int priority;
    int response = 0;
    int ctime = 0;
    int wtime = 0;
    int tat = 0;
}process[1000], que[1000],result[1000];

int process_num;
int k = 0, f = 0, r = 0;
int qt;

void insert() {
    //freopen("rr1.txt", "r", stdin);           //rr1.txt er input er jonno thikase
    //freopen("rr2.txt", "r", stdin);          
    freopen("rr.txt", "r", stdin);
    cin >> process_num;
    for(int i=0; i<process_num; i++) {
        cin >> process[i].pname;
        cin >> process[i].arrival;
        cin >> process[i].burst;
        cin >> process[i].priority;
    }
    cin >> qt;
}

bool aTimeSort(Process a, Process b) {
    return a.arrival < b.arrival;
}

bool burstTimeSort(Process a, Process b) {
    return a.burst < b.burst;
}

bool prioritySort(Process a, Process b) {
    return a.priority > b.priority;
}

void rr() {
    sort(process, process+process_num, aTimeSort);
    int current_time = 0, i, current_process;
    int timeArray[1000];
    bool moveLast = false;

    for(i=0; i<process_num || r>f; ) {
        current_process = i;
        while(process[current_process].arrival<=current_time && current_process!=process_num) {
            que[r] = process[current_process];
            r++;
            current_process++;
        }
        if(f==r) {
            result[k].pname = "idle";
            result[k].arrival = current_time;
            result[k].burst = process[current_process].arrival - current_time;
            current_time += result[k].burst;
            k++;
            continue;
        }
        i = current_process;
        if(moveLast==true){
            que[r]=que[f];
            f++;
            r++;
        }

        current_process = f;
        if(que[current_process].burst > qt) {
            result[k] = que[current_process];
            result[k].burst = qt;
            k++;
            que[current_process].burst -= qt;
            current_time += qt;
            moveLast = true;
        }
        else {
            result[k] = que[current_process];
            k++;
            f++;
            current_time += que[current_process].burst;
            moveLast = false;
        }

        if(f==r && i>=process_num) {
            break;
        }
    }

    timeArray[i] = current_time;
    current_time += process[i].burst;
    
    for(i=0; i<k-1; i++) {
        if(result[i].pname == result[i+1].pname) {
            result[i].burst += result[i+1].burst;
            for(current_process=i+1; current_process<k-1; current_process++) {
                result[current_process] = result[current_process+1];
            }
            k--;
            i--;
        }
    }

    int rtime = 0;
    for(current_process=0; current_process<process_num; current_process++) {
        rtime = 0;
        for(i=0; i<k; i++) {
            if(process[current_process].pname == result[i].pname) {
                process[current_process].response = rtime;
                break;
            }
            rtime += result[i].burst;
        }
    }

    double avgWT = 0;
    double avgRT = 0;
    double avgTAT = 0;

    cout << "\nGantt Chart:\n";
    rtime = 0;
    for(i=0; i<k; i++) {
        if(i!=k) {
            if(result[i].pname == "idle") {
                cout << "|-idle-";  
            }
            else cout << "|--P"<< result[i].pname << "--"; 
        }
        rtime += result[i].burst;
        for(current_process=0; current_process<process_num; current_process++) {
            if(process[current_process].pname == result[i].pname) {
                process[current_process].ctime = rtime;
            }
        }
    }
    cout << "|";

    //cout << k << endl;                k = 22
    cout << endl;
    rtime = 0;
    for(i=0; i<k+1; i++) {
        printf("%-7d", rtime);
        timeArray[i] = rtime;
        rtime += result[i].burst;
        //printf("Hi\n");
    }

    for(i=0; i<process_num; i++) {
        process[i].wtime = process[i].ctime-process[i].arrival-process[i].burst;
        avgWT += process[i].wtime;
        process[i].tat = process[i].ctime-process[i].arrival;
        avgTAT += process[i].tat;
    }

    cout << endl;
    cout << "\n";
    cout << "Process\t\tPriority\tAT\tBT\tCT\tTAT\tWT\n";
    for(i=0; i<process_num; i++) {
        if(process[i].pname == "") break;
        cout << "  P" << process[i].pname << "\t\t  ";
        cout << process[i].priority << "\t \t";
        cout << process[i].arrival << "\t";
        cout << process[i].burst << "\t";
        cout << process[i].ctime << "\t";
        cout << process[i].tat << "\t";
        cout << process[i].wtime << "\t";
        cout << "\n";
    }

    cout << "Average Waiting Time: " << (double)avgWT / (double)process_num << endl;
    cout << "Average Turnaround Time: " << (double)avgTAT / (double)process_num << endl;
}
 
int main (void) {

    insert();
    rr();

    return 0;
}