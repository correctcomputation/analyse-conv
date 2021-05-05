#!/bin/bash 
# Filter artifacts from 3C code

sed 's/_Unchecked//' | sed 's/#pragma CHECKED_SCOPE.*$//'
