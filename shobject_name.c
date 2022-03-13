/*
 * Replace the following string of 0s with your student number
 * 000000000
 */
#include <stdlib.h>
#include <stdio.h>
#include "sim_config.h"
#include "shobject_name.h"

const char* SHOBJ_NAME_FORMAT = "/csc2035.%.9s.%.12s";

/* 
 * TODO you must implement this function.
 *
 * Hints:
 * - from its specification in shobject_name.h this function may seem 
 *      complicated, in fact almost everything will be covered in C 
 *      programming module materials
 * - there is a library function for getting the current user from the 
 *      environment (use "anon" if the function returns NULL)
 */
char* shobject_name(char* name_buf, const char* label) {
    

    char* user = getenv("USER");
    if (!user) user = "anon";

    if (!label || !label[0] || label == "") label = "none";

    int i;

    if (name_buf){
   
    i = snprintf(name_buf,MAX_NAME_SIZE, SHOBJ_NAME_FORMAT,user,label);

//    if (i>-1) return name_buf;
//    snprintf(name_buf, MAX_NAME_SIZE, "/csc2035.anon.none");
//    return name_buf;

    return i < 0 ? NULL : name_buf;}
    
    char* new_name_buf = calloc(MAX_NAME_SIZE, sizeof(char));
    i = asprintf(&new_name_buf, SHOBJ_NAME_FORMAT, user, label);
    return i < 0 ? NULL : new_name_buf;
}
