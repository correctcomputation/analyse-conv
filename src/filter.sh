#!/bin/bash 
# Filter artifacts from 3C code

sed 's/_Unchecked//' | sed '/#pragma CHECKED_SCOPE.*$/d'
