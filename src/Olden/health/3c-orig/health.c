





#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "health.h"
#include <assert.h>

int max_level;
long max_time;
long long seed;

_Ptr<struct Village> alloc_tree(int level, int label, _Ptr<struct Village> back) {
  if (level == 0)
    return ((void*)0);
  else {
    _Ptr<struct Village> new = ((void *)0);
    int i;
    _Ptr<struct Village> fval _Checked[4] = {((void *)0)};

    new = (_Ptr<struct Village>)malloc<struct Village>(sizeof(struct Village));

    for (i = 3; i >= 0; i--)
      fval[i] = alloc_tree(level - 1, label*4 + i + 1, new);

    new->back = back;
    new->label = label;
    new->seed = label * (127773 + seed);
    new->hosp.personnel = (int)pow(2, level - 1);
    new->hosp.free_personnel = new->hosp.personnel;
    new->hosp.num_waiting_patients = 0;
    new->hosp.assess.forward = ((void*)0);
    new->hosp.assess.back = ((void*)0);
    new->hosp.assess.patient = ((void*)0);
    new->hosp.waiting.forward = ((void*)0);
    new->hosp.waiting.back = ((void*)0);
    new->hosp.waiting.patient = ((void*)0);
    new->hosp.inside.forward = ((void*)0);
    new->hosp.inside.back = ((void*)0);
    new->hosp.inside.patient = ((void*)0);
    new->hosp.up.forward = ((void*)0);
    new->hosp.up.back = ((void*)0);
    new->hosp.up.patient = ((void*)0);
    new->returned.back = ((void*)0);
    new->returned.forward = ((void*)0);

    for (i = 0; i < 4; i++)
      new->forward[i] = fval[i];

    return new;
  }
}


struct Results get_results(_Ptr<struct Village> village) {
  int i;
  _Ptr<struct List> list = ((void *)0);
  _Ptr<struct Patient> p = ((void *)0);
  struct Results fval _Checked[4];
  struct Results r1;

  r1.total_hosps = 0.0;
  r1.total_patients = 0.0;
  r1.total_time = 0.0;

  if (village == ((void*)0)) return r1;

  for (i = 3; i > 0; i--) {
    _Ptr<struct Village> V = village->forward[i];
    fval[i] = get_results(V);
  }

  fval[0] = get_results(village->forward[0]);

  for (i = 3; i >= 0; i--) {
    r1.total_hosps += fval[i].total_hosps;
    r1.total_patients += fval[i].total_patients;
    r1.total_time += fval[i].total_time;
  }

  list = village->returned.forward;
  while (list != ((void*)0)) {
    p = list->patient;
    r1.total_hosps += (float)(p->hosps_visited);
    r1.total_time += (float)(p->time);
    r1.total_patients += 1.0;
    list = list->forward;
  }

  return r1;
}

void check_patients_inside(_Ptr<struct Village> village, _Ptr<struct List> list)
{
  _Ptr<struct List> l = ((void *)0);
  _Ptr<struct Patient> p = ((void *)0);
  int t;

  while (list != ((void*)0)) {
    p = list->patient;
    t = p->time_left;
    p->time_left = t - 1;
    if (p->time_left == 0) {
      t = village->hosp.free_personnel;
      village->hosp.free_personnel = t+1;
      l = &(village->hosp.inside);
      removeList(l, p);
      l = &(village->returned);
      addList(l, p); }
    list = list->forward;
  }
}

_Ptr<struct List> check_patients_assess(_Ptr<struct Village> village, _Ptr<struct List> list) {
  float rand;
  _Ptr<struct Patient> p = ((void *)0);
  _Ptr<struct List> up = ((void*)0);
  long long s;
  int label, t;

  while (list != ((void*)0)) {
    p = list->patient;
    t = p->time_left;
    p->time_left = t - 1;
    label = village->label;
    if (p->time_left == 0) {
      s = village->seed;
      rand = my_rand(s);
      village->seed = (long long)(rand * 2147483647);
      label = village->label;
      if (rand > 0.1 || label == 0) {
        removeList(&village->hosp.assess, p);
        addList(&village->hosp.inside, p);
        p->time_left = 10;
        t = p->time;
        p->time = t + 10;
      } else {
        t = village->hosp.free_personnel;
        village->hosp.free_personnel = t+1;

        removeList(&village->hosp.assess, p);
        up = &village->hosp.up;
        addList(up, p);
      }
    }

    list = list->forward;
  }
  return up;
}

void check_patients_waiting(_Ptr<struct Village> village, _Ptr<struct List> list) {
  int i, t;
  _Ptr<struct Patient> p = ((void *)0);

  while (list != ((void*)0)) {
    i = village->hosp.free_personnel;
    p = list->patient;
    if (i > 0) {
      t = village->hosp.free_personnel;
      village->hosp.free_personnel = t-1;
      p->time_left = 3;
      t = p->time;
      p->time = t + 3;

      removeList(&village->hosp.waiting, p);
      addList(&village->hosp.assess, p); }
    else {
      t = p->time;
      p->time = t + 1; }
    list = list->forward; }
}


void put_in_hosp(_Ptr<struct Hosp> hosp, _Ptr<struct Patient> patient) {
  int t = patient->hosps_visited;

  patient->hosps_visited = t + 1;
  if (hosp->free_personnel > 0) {
    t = hosp->free_personnel;
    hosp->free_personnel = t-1;
    addList(&hosp->assess, patient);
    patient->time_left = 3;
    t = patient->time;
    patient->time = t + 3;
  } else {
    addList(&hosp->waiting, patient);
  }
}

_Ptr<struct Patient> generate_patient(_Ptr<struct Village> village)
{
  long long s,newseed;
  _Ptr<struct Patient> patient = ((void *)0);
  float rand;
  int label;

  s = village->seed;
  rand = my_rand(s);
  village->seed = (long long)(rand * 2147483647);
  newseed = village->seed;
  label = village->label;
  if (rand > 0.666) {
    patient = (_Ptr<struct Patient>)malloc<struct Patient>(sizeof(struct Patient));
    patient->hosps_visited = 0;
    patient->time = 0;
    patient->time_left = 0;
    patient->home_village = village;
    return patient;
  }
  return ((void*)0);
}

int main(int argc, _Array_ptr<char *> argv : count(argc))
{
  struct Results results;
  _Ptr<struct Village> top = 0;
  int i;
  float total_time, total_patients, total_hosps;

  dealwithargs(argc, argv);
  top = alloc_tree(max_level, 0, top);

  printf("\n\n    Columbian Health Care Simulator\n\n");
  printf("Working...\n");

  for (i = 0; i < max_time; i++) {
    if ((i % 50) == 0) printf("%d\n", i);
    sim(top);
  }

  printf("Getting Results\n");
  results = get_results(top);
  total_patients = results.total_patients;
  total_time = results.total_time;
  total_hosps = results.total_hosps;

  printf("Done.\n\n");
  printf("# of people treated:              %f people\n",
    total_patients);
  printf("Average length of stay:           %0.2f time units\n",
    total_time / total_patients);
  printf("Average # of hospitals visited:   %f hospitals\n\n",
    total_hosps / total_patients);

  return 0;
}


_Ptr<struct List> sim(_Ptr<struct Village> village)
{
  int i;
  _Ptr<struct Patient> patient = ((void *)0);
  _Ptr<struct List> l = ((void *)0);
  _Ptr<struct List> up = ((void *)0);
  _Ptr<struct Hosp> h = ((void *)0);
  _Ptr<struct List> val _Checked[4] = {((void *)0)};

  int label;
  if (village == ((void*)0)) return ((void*)0);

  label = village->label;

  for (i = 3; i > 0; i--) {
    _Ptr<struct Village> V = village->forward[i];
    _Ptr<struct List> L = sim(V);
    val[i] = L;
  }

  val[0] = sim(village->forward[0]);
  h = &village->hosp;

  for (i = 3; i >= 0; i--) {
    _Ptr<struct List> valI = l = val[i];
    if (l != ((void*)0)) {
      l = l->forward;
      while (l != ((void*)0)) {
 put_in_hosp(h, l->patient);
 removeList(valI, l->patient);
        l = l->forward;
      }
    }
  }

  check_patients_inside(village, village->hosp.inside.forward);
  up = check_patients_assess(village, village->hosp.assess.forward);
  check_patients_waiting(village, village->hosp.waiting.forward);


  if ((patient = generate_patient(village)) != ((void*)0)) {
    label = village->label;
    put_in_hosp(&village->hosp, patient);
  }

  return up;
}
