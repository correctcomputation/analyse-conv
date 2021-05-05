/* For copyright information, see olden_v1.0/COPYRIGHT */

/********************************************************************
 *  List.c:  Handles lists.                                         *
 *           To be used with health.c                               *
 ********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "health.h"
#pragma CHECKED_SCOPE ON

void addList(_Ptr<struct List> list, _Ptr<struct Patient> patient) {
  _Ptr<struct List> b = NULL;

  while (list != NULL) {
    b = list;
    list = list->forward; }
  
  list = calloc<struct List>(1, sizeof(struct List));
  list->patient = patient;
  list->forward = NULL;
  list->back = b;
  b->forward = list;
} 

void removeList(_Ptr<struct List> list, _Ptr<struct Patient> patient) {
  _Ptr<struct List>      l1 = NULL;
  _Ptr<struct List>      l2 = NULL;
  _Ptr<struct Patient>   p = list->patient;

  while(p != patient) {
      list = list->forward; 
      p = list->patient;
  }
    
  l1 = list->back;
  l2 = list->forward;
  l1->forward = l2;
  if (list->forward != NULL) {
    l1 = list->forward;
    l2 = list->back;
    l1->back = l2;
  }
  /*free(list);*/
}
     
