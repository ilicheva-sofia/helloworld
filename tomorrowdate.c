#include <stdio.h>
#include <locale.h>
#include <time.h>
int main(){ 
    struct tm tm = {};
    time_t tom_time;
    char buff[256];
    fgets (buff, sizeof buff, stdin);
    strptime(buff, "%d/%m/%Y %H:%M", &tm);
    tom_time = mktime(&tm);
    tom_time = tom_time + 60*60*24;
    struct tm *tom_time_tm = localtime(&tom_time);
    setlocale (LC_TIME, "ru_RU.utf8");
    strftime (buff, sizeof buff, "%d/%m/%Y %H:%M", tom_time_tm);
    puts (buff); 
    return 0;
    
}