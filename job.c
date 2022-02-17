/*
 * Replace the following string of 0s with your student number
 * 000000000
 */
#include <stdlib.h>
#include "job.h"

/* 
 * DO NOT EDIT the job_new function.
 */
job_t* job_new(pid_t pid, unsigned int id, const char* label) {
    return job_set((job_t*) malloc(sizeof(job_t)), pid, id, label);
}

/* 
 * TODO: you must implement this function
 * Hint:
 * - look for other functions in this file that you can use to implement 
 *      this function
 */
job_t* job_copy(job_t* dst, job_t* src) {
    return src;
}

/* 
 * TODO: you must complete the implementation of this function, which 
 * currently only sets the pid and id fields of a job to zero.
 */
void job_init(job_t* job) {
    job->pid = 0;
    job->id = 0;
}

/* 
 * TODO: you must complete the implementation of this function, which 
 * currently only compares the pid and id fields of a job.
 */
bool job_is_equal(job_t* j1, job_t* j2) {
    return j1->pid == j2->pid && j1->id == j2->id;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - read the information in job.h about padding and truncation of job labels
 */
job_t* job_set(job_t* job, pid_t pid, unsigned int id, const char* label) {
    return job;
}

/* 
 * TODO: you must implement this function
 * Hint:
 * - look at the allocation of a job in job_new
 */
void job_delete(job_t* job) {
    return;
}