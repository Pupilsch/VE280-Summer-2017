#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"
using namespace std;

enum type_of_status{
    platinum,gold,silver,regular,status_size
};

const char *status_str[] = {"platinum", "gold", "silver", "regular"};

struct caller{//a struct represent a single caller
    unsigned int timestamp;
    string name;
    type_of_status status;
    unsigned int waiting;
    unsigned int duration;
    int pick_up_time=-1; //if agent pick this one, modifies the pick_up_time
};

void read_file(Dlist<caller> &cal,Dlist<caller> &pl,Dlist<caller> &gl,Dlist<caller> &sl,Dlist<caller> &rl,Dlist<caller> &cl){
    //Requires: correct input
    //modifies: initialize the 6 Dlist which store the caller.
    int num=0;
    unsigned int r_time;
    string r_name;
    string r_status;
    unsigned int r_waiting;
    unsigned int r_duration;
    cin>>num;
    for(int i=0;i<num;i++){
        caller *a=new caller;
        caller *b=new caller;
        cin>>r_time;
        cin>>r_name;
        cin>>r_status;
        cin>>r_waiting;
        cin>>r_duration;
        for(int j=0;j<status_size;j++){
            if(r_status==status_str[j]) a->status=type_of_status(j);
        }
        a->timestamp=r_time;
        a->name=r_name;
        a->waiting=r_waiting;
        a->duration=r_duration;
        cal.insertBack(a);//call list stores all the caller in turn.
        for(int j=0;j<status_size;j++){
            if(r_status==status_str[j]) b->status=type_of_status(j);
        }
        b->timestamp=r_time;
        b->name=r_name;
        b->waiting=r_waiting;
        b->duration=r_duration;
        if(b->status==platinum) pl.insertBack(b);
        if(b->status==gold) gl.insertBack(b);
        if(b->status==silver) sl.insertBack(b);
        if(b->status==regular) rl.insertBack(b);
        //other four list store the status's caller
    }
}

void agent_exam(Dlist<caller> &op, unsigned int time){
    //MODIFIES: check whether the call is over and clean the current list
    if(!op.isEmpty()){
        caller *temp;
        temp=op.removeFront();
        int t_1=time-temp->pick_up_time;
        int t_2=temp->duration;
        if(t_1==t_2){
            delete temp;
        }
        else op.insertBack(temp);
    }
}

void call_exam(Dlist<caller> &op, unsigned int time){
    //MODIFIES: to show the call and remove caller from call list after cout
    while(true) {
        if(op.isEmpty())break;
        caller *temp;
        temp = op.removeFront();
        if(temp->timestamp != time) {
            op.insertFront(temp);
            break;
        }
        if (temp->timestamp == time) {
            cout << "Call from " << temp->name << " a " << status_str[temp->status] << " member" << endl;
            delete temp;
        }
    }
    return;
}

void hang_up(Dlist<caller> &op,unsigned time){
    //MODIFIES: see if  members of a status list is hang up and removed from the Dlist
    if(op.isEmpty()) return;
    else{
        caller *temp;
        temp = op.removeFront();
        int compare=time-(temp->timestamp);
        int t_w=temp->waiting;
        if(compare>=t_w){
            cout<<temp->name<<" hangs up"<<endl;
            delete temp;
        }
        hang_up(op,time);
        if(compare<t_w){
            op.insertFront(temp);
        }
    }
}

void status_exam(Dlist<caller> &agent,Dlist<caller> &op,unsigned int time){
    //MODIFIES: see if members of a status list can be answered
    while(true){
        if(op.isEmpty())break;
        caller *temp;
        temp = op.removeFront();
        if(temp->timestamp > time) {
            op.insertFront(temp);
            break;
        }
        if (temp->timestamp <= time) {
            if(agent.isEmpty()) {
                temp->pick_up_time=time;
                agent.insertBack(temp);
                cout<<"Answering call from "<<temp->name<<endl;
                break;
            }
            else {
                op.insertFront(temp);
                break;
            }
        }
    }
}

int main() {
    unsigned int time=0;
    Dlist<caller> call_list;//call list stores all the caller in turn.
    Dlist<caller> platinum_list;//other four list store the status's caller
    Dlist<caller> gold_list;
    Dlist<caller> silver_list;
    Dlist<caller> regular_list;
    Dlist<caller> current_list;//current list stores the caller who is talking to the agent
    read_file(call_list,platinum_list,gold_list,silver_list,regular_list,current_list);
    while(time==0 || !call_list.isEmpty() || !platinum_list.isEmpty() || !gold_list.isEmpty() || !silver_list.isEmpty() || !regular_list.isEmpty() || !current_list.isEmpty()){
        //exit when all list is empty
        cout<<"Starting tick #"<<time<<endl;
        agent_exam(current_list, time);
        hang_up(platinum_list, time);
        hang_up(gold_list, time);
        hang_up(silver_list, time);
        hang_up(regular_list, time);
        call_exam(call_list, time);
        status_exam(current_list, platinum_list, time);
        status_exam(current_list, gold_list, time);
        status_exam(current_list, silver_list, time);
        status_exam(current_list, regular_list, time);
        time++;
    }
    return 0;
}