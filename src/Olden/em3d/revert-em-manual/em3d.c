

#include "em3d.h"
int nonlocals=0;
void compute_nodes(register node_t * nodelist)
{
  register int i;
  register node_t * localnode = ((void*)0);

  for (; nodelist; ) {
    register double cur_value;
    register int from_count ;
    register double * other_value = ((void*)0);
    register double coeff;
    register double value;



    localnode = nodelist;
    cur_value = *localnode->value;
    from_count = localnode->from_count-1;
    for (i=0; i < from_count; i+=2) {
      other_value = localnode->from_values[i];
      coeff = localnode->coeffs[i];

      if (other_value)
        value = *other_value;
      else
        value = 0;

      cur_value -= coeff*value;
      other_value = localnode->from_values[i+1];
      coeff = localnode->coeffs[i];

      if (other_value)
        value = *other_value;
      else
        value = 0;

      cur_value -= coeff*value;


    }

    if (i==from_count) {
      other_value = localnode->from_values[i];
      coeff = localnode->coeffs[i];

      if (other_value)
        value = *other_value;
      else
        value = 0;

      cur_value -= coeff*value;
    }
    *localnode->value = cur_value;
    nodelist = localnode->next;
  }
}
