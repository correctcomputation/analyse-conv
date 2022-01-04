






#ifndef _HEALTH
#define _HEALTH

#include <stdio.h>
#include <stdlib.h>

#define chatting printf

#define IA 16807
#define IM 2147483647
#define AM (1.0 / IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

extern int max_level;
extern long max_time;
extern long long seed;

struct Results {
  float total_patients;
  float total_time;
  float total_hosps;
};

struct Patient {
  int hosps_visited;
  int time;
  int time_left;
  _Ptr<struct Village> home_village;
};

struct List {
  _Ptr<struct List> forward;
  _Ptr<struct Patient> patient;
  _Ptr<struct List> back;
};

struct Hosp {
  int personnel;
  int free_personnel;
  int num_waiting_patients;
  struct List waiting;
  struct List assess;
  struct List inside;
  struct List up;
};

struct Village {
  _Ptr<struct Village> forward _Checked[4];
  _Ptr<struct Village> back;
  struct List returned;
  struct Hosp hosp;
  int label;
  long long seed;
};

_Ptr<struct Village> alloc_tree(int level, int label, _Ptr<struct Village> back);
void dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc));
float my_rand(long long idum);
_Ptr<struct Patient> generate_patient(_Ptr<struct Village> village);
void put_in_hosp(_Ptr<struct Hosp> hosp, _Ptr<struct Patient> patient);
void addList(_Ptr<struct List> list, _Ptr<struct Patient> patient);
void removeList(_Ptr<struct List> list, _Ptr<struct Patient> patient);
_Ptr<struct List> sim(_Ptr<struct Village> village);
void check_patients_inside(_Ptr<struct Village> village, _Ptr<struct List> list);
_Ptr<struct List> check_patients_assess(_Ptr<struct Village> village, _Ptr<struct List> list);
void check_patients_waiting(_Ptr<struct Village> village, _Ptr<struct List> list);
struct Results get_results(_Ptr<struct Village> village);

#endif

