#include<stdio.h>
#include<stdarg.h>
#include<time.h>
#include<stdexcept>
#include<map>
#include<string>

using c_string = const char*;

class Logger{
    FILE* out_file;
    FILE* err_file;
    std::map<std::string, time_t> timers;

    public:
    /*Create logger object where 
    - outfile is the file where the output logs will written to defaults to stdout
    - errfile is the file where the error logs will be written to defaults to stderr
    if an outfile is set and the errfile is null, errfile will be set equal to outfile
    */
    Logger(c_string outfile = NULL, c_string errfile = NULL);
    ~Logger();
    /*Write to the outfile works similar to prinf
    */
    int log(c_string format, ...);
    /*Write to the errfile works similar to prinf
    */
    int error(c_string format, ...);
    /*Create new timer, identified by its lable
    */
    void newTimer(const std::string&  time_lable);
    /*Log message to the outfile and ad the selected timer at the end of the message
    */
    int logTimer(const std::string&  time_lable, c_string  format, ...);
    /*Log message to the outfile and ad the selected timer at the end of the message
    selected timer is deleted after this call
    */
    int endTimer(const std::string&  time_lable, c_string  format, ...);
    /*Write to the outfile with the current time formatted as time_format at the end
    */
    int timeLog(const std::string&  time_format, c_string  format, ...);
    /*set the outfile
    */
    void setOutfile(c_string filename);
    /*set the errfile
    */
    void setErrfile(c_string filename);
};