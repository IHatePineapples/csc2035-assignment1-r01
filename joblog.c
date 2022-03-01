/*
 * Replace the following string of 0s with your student number
 * 000000000
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "joblog.h"

// DO NOT EDIT the following definitions of log string constant values */
const char* JOBLOG_PATH = "./out";
const char* JOBLOG_NAME_FMT = "%s/%s%07d.txt";
const char* JOBLOG_ENTRY_FMT = "pid:%07d,id:%05d,label:%s\n";

/* 
 * DO NOT EDIT the new_log_name function. It is a private helper 
 * function provided for you to create a log name from a process 
 * descriptor for use when reading, writing and deleting a log file.
 * 
 * You must work out what the function does in order to use it properly
 * and to clean up after use.
 *
 * See JOBLOG_NAME_FMT above for the form of log names.
 */
static char* new_log_name(proc_t* proc) {
    if (!proc)
        return NULL;

    char* log_name;
            
    asprintf(&log_name, JOBLOG_NAME_FMT, JOBLOG_PATH, proc->type_label,
        proc->id);

    return log_name;
}

/* 
 * DO NOT EDIT the joblog_init function.
 */
int joblog_init(proc_t* proc) {
    if (!proc) {
        errno = EINVAL;
        return -1;
    }
        
    int r = 0;
    if (proc->is_init) {
        struct stat sb;
    
        if (stat(JOBLOG_PATH, &sb) != 0) {
            errno = 0;
            r = mkdir(JOBLOG_PATH, 0777);
        }  else if (!S_ISDIR(sb.st_mode)) {
            unlink(JOBLOG_PATH);
            errno = 0;
            r = mkdir(JOBLOG_PATH, 0777);
        }
    }

    joblog_delete(proc);    // in case log exists for proc
    
    return r;
}

/* 
 * TODO: you must implement this function.
 * Hints:
 * - you have to go to the beginning of the line represented
 *      by entry_num to read the required entry
 * - see malloc and calloc system library functions for dynamic allocation, 
 *      and the documentation in joblog.h for when to do dynamic allocation
 */
char* joblog_read_entry(proc_t* proc, int entry_num, char* buf) {

    int init_errno = errno;


    if (!proc) {
        //errno = entry_errno;
        return NULL;
    }
    if (entry_num <0) {
        //errno = entry_errno;
        return NULL;
    }

    char* f_name = new_log_name(proc);

    if (!f_name){
        errno = init_errno;
        free(f_name);
        return NULL;
    };
    FILE* f = fopen(f_name, "r");
    free(f_name);
    if (!f) {
        errno = init_errno;
        return NULL;
    }

    //int r_fseek = fseek(f, entry_num * (JOBLOG_ENTRY_SIZE - 1), SEEK_SET);
    int r_fseek = fseek(f, entry_num * (JOBLOG_ENTRY_SIZE - 1), SEEK_SET);
    char s[JOBLOG_ENTRY_SIZE];
    char * r_fgets1 = fgets(s,JOBLOG_ENTRY_SIZE,f);
    if (r_fseek > -1){
        errno = init_errno;
        return NULL;
    }
    if (!r_fgets1){
        errno = init_errno;
        free(r_fgets1);
        return NULL;

    }


    if (buf) {
        char *r_fgets = fgets(buf,JOBLOG_ENTRY_SIZE,f);

        if (!r_fgets){
            errno = init_errno;
            free(r_fgets);
            return NULL;

        }

        buf[JOBLOG_ENTRY_SIZE - 1] = '\0';

        fclose(f);
        free(r_fgets);
        return buf;

    }
    else{

        return buf;
        //char* new_buf = malloc()
    }
}

/* 
 * TODO: you must implement this function.
 * Hints:
 * - look at the documentation of the format of a log entry in joblog.h
 * - remember new entries are appended to a log file
 */
void joblog_write_entry(proc_t* proc, job_t* job) {

    int init_errno = errno;

    if (!proc) return;
    if (!job) return;

    char* f_name = new_log_name(proc);

    if (!f_name){
        errno = init_errno;
        free(f_name);
        return;
    }

    //"pid:%07d,id:%05d,label:%s\n"
    FILE* f = fopen(f_name, "a");
    free(f_name);
    if (!f) {
        errno = init_errno;
        return;
    }
    fprintf(f,JOBLOG_ENTRY_FMT,job->pid, job->id, job->label );
    //printf(JOBLOG_ENTRY_FMT,job->pid, job->id, job->label );

    fclose(f);


    errno = init_errno;

}

/* 
 * TODO: you must implement this function.
 */
void joblog_delete(proc_t* proc) {
    if (!proc)
        return;
    char* logfile_name = new_log_name(proc);
    remove(logfile_name);
    free(logfile_name);
}