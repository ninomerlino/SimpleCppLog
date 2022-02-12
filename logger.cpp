#include"logger.h"
#define timestamp time(NULL)

Logger::Logger(c_string outfile, c_string errfile){
        setOutfile(outfile);
        setErrfile(errfile);
        timers = {};
}
Logger::~Logger(){
        if(out_file && out_file != stdout){
            fclose(out_file);
        }
        if(err_file && err_file != stderr){
            fclose(err_file);
        }
}
int Logger::log(c_string format, ...){
        va_list args;
        int printed;
        va_start(args, format);
        printed = vfprintf(out_file, format, args);
        va_end(args);
        putc('\n',out_file);
        return printed;
}
int Logger::error(c_string format, ...){
        va_list args;
        int printed;
        va_start(args, format);
        printed = vfprintf(err_file, format, args);
        va_end(args);
        putc('\n',out_file);
        return printed;
}
void Logger::newTimer(const std::string& time_lable){
        timers[time_lable] = timestamp;
}
int Logger::logTimer(const std::string& time_lable,c_string format, ...){
        time_t delta = timestamp - timers[time_lable];
        va_list args;
        int printed;
        va_start(args, format);
        printed = vfprintf(err_file, format, args);
        va_end(args);
        fprintf(out_file, " %lds\n",delta);
        return printed;
}
int Logger::endTimer(const std::string& time_lable,c_string format, ...){
        time_t delta = timestamp - timers[time_lable];
        va_list args;
        int printed;
        va_start(args, format);
        printed = vfprintf(err_file, format, args);
        va_end(args);
        fprintf(out_file, " %lds\n",delta);
        timers.erase(time_lable);
        return printed;
}
int Logger::timeLog(const std::string& time_format,c_string format, ...){
        tm* time_info;
        va_list args;
        int printed;
        char time_string[500];
        const time_t ts = time(NULL);
        localtime_r(&ts, time_info);
        va_start(args, format);
        printed = vfprintf(err_file, format, args);
        va_end(args);
        strftime(time_string, 100, time_format.c_str(), time_info);
        fprintf(out_file, " %s\n", time_string);
        return printed;
}
void Logger::setOutfile(c_string filename){
        if(filename == NULL){
            out_file = stdout;
        }else{
            out_file = fopen(filename, "w");
            if(!out_file){
                throw std::runtime_error("cannot open logger output file");
            }
        }
}
void Logger::setErrfile(c_string filename){
        if(filename == NULL){
            if(out_file != stdout){
                err_file = out_file;
            }else{
                err_file = stderr;
            }
        }else{
            err_file = fopen(filename, "w");
            if(!err_file){
                throw std::runtime_error("cannot open logger error file");
            }
        }
}