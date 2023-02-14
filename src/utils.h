#ifndef UTILS_H
#define UTILS_H

#define DEBUG 1

#ifdef DEBUG
  #define DEBUG_OUT(cont)  Serial.println(cont)
#else
  #define DEBUG_OUT(cont)
#endif

#endif