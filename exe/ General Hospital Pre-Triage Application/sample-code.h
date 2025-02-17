/* Citation and Sources...
Final Project Milestone 3
Module: Patient
Filename: Patient.h
Version 1.0
Author   Raya Sophia Casas
Revision History
-----------------------------------------------------------
Date        Reason
2024/03/23  Preliminary release
2024/04/03  Added query methods
2024/04/03  Removed getValidInt
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SENECA_PATIENT_H
#define SENECA_PATIENT_H
#include <iostream>
#include "IOAble.h"
#include "Ticket.h"

namespace seneca {
    class Patient : public IOAble {
        char* m_name{};
        int m_ohip = 0;
        Ticket m_ticket = 0;
    public:
        Patient(int ticketNum);
        Patient(const Patient& patient);
        Patient& operator=(const Patient& patient);
        virtual ~Patient();

        virtual char type() const = 0;
        bool operator==(char input) const;
        bool operator==(const Patient& patient) const;
        void setArrivalTime();
        Time time() const;
        int number() const;

        char* name() const;
        int ohip() const;
        int ticket() const;

        operator bool() const;
        operator const char* () const;

        std::ostream& write(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
    };
}
#endif // !SENECA_PATIENT_H
