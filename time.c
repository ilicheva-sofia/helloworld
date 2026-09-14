#include <stdio.h>
#include <locale.h>
#include <time.h>
int main(){
    char buff[256]; time_t curr_time; time(&curr_time);
    struct tm *curr_time_tm = localtime(&curr_time);
    setlocale(LC_TIME, "ru_RU.utf8");
    strftime(buff, sizeof buff, "%d/%m/%Y %H:%M", curr_time_tm);
    puts(buff);
    return 0;
}