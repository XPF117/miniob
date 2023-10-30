#pragma once
#include <stdint.h>
#include<stdio.h>
#include<string>
#include<sstream>
#include"common/rc.h"
#include"sql/parser/parse_defs.h"

inline bool is_leap_year(int year)
{
    return (year %4 == 0 && year % 100 != 0) || year % 400 == 0;
}

inline RC string_to_date(const char *str, int &date)
{
    //“2022-06-01"
    //"2022-6-1"
    int year = 0;
    int month = 0;
    int day = 0;
    int ret = sscanf(str,"%d-%d-%d",&year, &month, &day);
    if (ret != 3){
        return RC::FUILIRE;
    }
    // validate
    if (year < 1900 || year > 9999 || 
    (month <= 0 || month > 12) ||
    (day <= 0 || day > 31)){
        return RC::FUILIRE;
    }
    int max_day_in_month[] = {31, 29, 31, 30, 31, 30,31, 31, 30,31, 30, 31};
    const int max_day = max_day_in_month[month - 1];
    if (day > max_day){
        return RC::FUILIRE;
    }
    if (month == 2 && !is_leap_year(year) && day > 28){
        return RC::FUILIRE;
    }
    date = year * 10000 + month * 100 + day; // 20220601
    return RC::SUCCESS;

}

inline std::string date_to_string(int date)
{
    // 将int类型的日期转换为字符串流
    std::stringstream ss;
    ss << date;

    // 从字符串流中读取年、月、日
    std::string dateStr = ss.str();
    std::string year = dateStr.substr(0, 4);
    std::string month = dateStr.substr(4, 2);
    std::string day = dateStr.substr(6, 2);

    // 拼接成格式化的日期字符串
    std::string formattedDate = year + "-" + month + "-" + day;

    return formattedDate;
}
