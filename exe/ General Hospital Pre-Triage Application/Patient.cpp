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
2024/03/28  Fixed read func clear and write func ignore
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "Utils.h"

using namespace std;
namespace seneca {
	Patient::Patient(int ticketNum) : m_ticket(ticketNum)
	{
	}
	Patient::Patient(const Patient& patient)
	{
		m_name = new char[strlen(patient.m_name) + 1];
		strcpy(m_name, patient.m_name);
		m_ohip = patient.m_ohip;
		m_ticket = patient.m_ticket;
	}
	Patient& Patient::operator=(const Patient& patient)
	{
		if (this != &patient) {
			delete[] m_name;
			m_name = new char[strlen(patient.m_name) + 1];
			strcpy(m_name, patient.m_name);
			m_ohip = patient.m_ohip;
			m_ticket = patient.m_ticket;
		}
		return *this;
	}
	Patient::~Patient()
	{
		delete[] m_name;
		m_name = nullptr;
		m_ohip = 0;
		m_ticket = 0;
	}
	bool Patient::operator==(char input) const
	{
		return type() == input;
	}
	bool Patient::operator==(const Patient& patient) const
	{
		return type() == patient.type();
	}
	void Patient::setArrivalTime()
	{
		m_ticket.resetTime();
	}
	Time Patient::time() const
	{
		return m_ticket.time();
	}
	int Patient::number() const
	{
		return m_ticket.number();
	}
	char* Patient::name() const
	{
		return m_name;
	}
	int Patient::ohip() const
	{
		return m_ohip;
	}
	int Patient::ticket() const
	{
		return m_ticket.number();
	}
	Patient::operator bool() const
	{
		return m_name != nullptr;
	}
	Patient::operator const char* () const
	{
		return m_name;
	}
	std::ostream& Patient::write(std::ostream& ostr) const
	{
		if (&ostr == &clog) {
			if (m_name == nullptr) {
				ostr << "Invalid Patient Record";
			}
			else {
				ostr.setf(ios::left);
				ostr << m_name;
				ostr.width(59);
				ostr.fill('.');
				ostr.setf(ios::right);
				ostr << m_ohip;
				ostr.fill(' ');
				ostr.width(5);
				ostr << m_ticket.number() << " " << m_ticket.time();
			}
		}
		else if (&ostr == &cout) {
			if (m_name == nullptr) {
				ostr << "Invalid Patient Record" << endl;
			}
			else {
				m_ticket.write(ostr);
				ostr << endl;
				ostr << m_name << ", OHIP: " << m_ohip << endl;
			}
		}
		else {
			ostr << type() << ',' << m_name << ',' << m_ohip << ',';
			m_ticket.write(ostr);
		}
		return ostr;
	}
	std::istream& Patient::read(std::istream& istr)
	{
		delete[] m_name;
		m_name = nullptr;
		if (&istr == &cin) {
			cout << "Name: ";
			char tempName[51];
			istr.get(tempName, 51);
			istr.ignore(10000, '\n');
			if (m_name == nullptr) {
				m_name = new char[strlen(tempName) + 1];
				strcpy(m_name, tempName);
			}
			cout << "OHIP: ";
			m_ohip = U.getValidInt(100000000, 999999999);
			if (!istr) {
				delete[] m_name;
				m_name = nullptr;
			}
			istr.clear();
			istr.ignore(10000, '\n');
		}
		else {
			char tempName[51];
			istr.get(tempName, 51, ',');
			istr.ignore(10000, ',');
			if (m_name == nullptr) {
				m_name = new char[strlen(tempName) + 1];
				strcpy(m_name, tempName);
			}
			istr >> m_ohip;
			if (!istr) {
				delete[] m_name;
				m_name = nullptr;
			}
			istr.ignore(); // to ignore comma
			m_ticket.read(istr);
		}
		return istr;
	}
}