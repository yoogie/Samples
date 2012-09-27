#pragma once
#ifndef __COMPANY_H__
#define __COMPANY_H__

//#define KEY 0
#define TU8 unsigned char

namespace COMPANY
{
    class Company
    {
    public:
        Company(const int time, const TU8 index, const int id);
        virtual ~Company();

        int Time() const; //GetTime(), getTime(), get_time()

        static const int KEY = 1; //cKey, mKey

    private:
        Company();
        Company (const Company& t);
        Company& operator=(const Company& t);

        int mTime;  //time,  m_time,  Time
        TU8 mIndex; //index, m_index, Index

        const int mId; //cId, m_id, Id
    };
}
#endif
