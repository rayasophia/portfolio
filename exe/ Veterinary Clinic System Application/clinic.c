/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Raya Sophia Casas
Student ID#: 101868230
Email      : rsmcasas@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

void sort(struct Appointment appoints[], int max)
{
    int i, j;
    struct Appointment temp;

    for (i = 0; i < max; i++)
    {
        appoints[i].time.min = (appoints[i].date.year * 12 * 30 * 24 * 60) +
            (appoints[i].date.month * 30 * 24 * 60) +
            (appoints[i].date.day * 24 * 60) +
            (appoints[i].time.hour * 60) +
            appoints[i].time.min;
    }
    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (appoints[j].time.min > appoints[j + 1].time.min)
            {
                temp = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < max; i++)
    {
        appoints[i].time.min = appoints[i].time.min -
            (appoints[i].date.year * 12 * 30 * 24 * 60) -
            (appoints[i].date.month * 30 * 24 * 60) -
            (appoints[i].date.day * 24 * 60) -
            (appoints[i].time.hour * 60);
    }
}


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    if (max == 0)
    {
        printf("*** No records found ***\n");
        return;
    }
    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }
    for (i = 0; i < max; ++i)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
        }
    }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int searchOption;
    printf("Search Options\n"
        "==========================\n"
        "1) By patient number\n"
        "2) By phone number\n"
        "..........................\n"
        "0) Previous menu\n"
        "..........................\n"
        "Selection: ");
    searchOption = inputIntRange(0, 2);
    if (searchOption == 1)
    {
        searchPatientByPatientNumber(patient, max);
    }
    else if (searchOption == 2)
    {
        searchPatientByPhoneNumber(patient, max);
    }
    else
    {
        clearInputBuffer();
    }
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int index = -1;
    int i;
    for (i = 0; i < max; ++i)
    {
        if (patient[i].patientNumber == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
        return;
    }
    int newPatientNumber = nextPatientNumber(patient, max);
    patient[index].patientNumber = newPatientNumber;
    inputPatient(&patient[index]);
    clearInputBuffer();
    printf("*** New patient record added ***\n\n");
}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNumber;
    int patientIndex;
    printf("Enter the patient number: ");
    patientNumber = inputInt();
    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);
    clearInputBuffer();

    if (patientIndex != -1)
    {
        menuPatientEdit(&patient[patientIndex]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNumber;
    int patientIndex;
    char confirmation;

    printf("Enter the patient number: ");
    patientNumber = inputInt();
    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);
    clearInputBuffer();

    if (patientIndex != -1)
    {
        displayPatientData(&patient[patientIndex], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        confirmation = inputCharOption("yn");

        if (confirmation == 'y')
        {
            patient[patientIndex].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i, j;
    sort(data->appointments, data->maxAppointments);
    displayScheduleTableHeader(NULL, 1);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber)
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                    break;
                }
            }
        }
    }

    printf("\n");
}




// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int lastDay = 31;
    int i, j = 0;
    struct Date date;

    printf("Year        : ");
    date.year = inputIntPositive();
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);
    printf("Day (1-");
    if (date.year % 4 == 0 && date.month == 2)
    {
        lastDay = 29;
    }
    else if (date.month == 2)
    {
        lastDay = 28;
    }
    else if (date.month == 4 || date.month == 9 || date.month == 11)
    {
        lastDay = 30;
    }
    printf("%d)  : ", lastDay);
    date.day = inputIntRange(1, lastDay);
    printf("\n");

    sort(data->appointments, data->maxAppointments);
    displayScheduleTableHeader(&date, 0);
    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber)
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    if (data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day)
                    {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    }
                }
            }
        }
    }
    printf("\n");
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appoints, int maxAppointments, struct Patient* patients, int maxPatients)
{
    struct Date date;    
    struct Time time;
    int lastDay = 31;
    int patientNumber, index, slotNotAvailable = 1;
    printf("Patient Number: ");    
    patientNumber = inputIntPositive();    
    index = findPatientIndexByPatientNum(patientNumber, patients, maxPatients);
    if (index >= 0)
    {
        while (slotNotAvailable)
        {
            printf("Year        : ");
            date.year = inputIntPositive();
            printf("Month (1-12): ");            
            date.month = inputIntRange(1, 12);
            printf("Day (1-");
            if (date.year % 4 == 0 && date.month == 2)
            {
                lastDay = 29;
            }
            else if (date.month == 2)
            {
                lastDay = 28;
            }
            else if (date.month == 4 || date.month == 9 || date.month == 11)
            {
                lastDay = 30;
            }
            printf("%d)  : ", lastDay);
            date.day = inputIntRange(1, lastDay);
            printf("Hour (0-23)  : ");            
            time.hour = inputIntRange(0, 23);           
            printf("Minute (0-59): ");            
            time.min = inputIntRange(0, 59);
            if (timeSlotAvailable(date, time, appoints, maxAppointments))
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else
            {
                while ((time.hour < START_HOUR || time.hour > END_HOUR) || (time.hour == END_HOUR && time.min > 0) || (time.min % MINUTE_INTERVAL != 0))
                {
                    printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);
                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);
                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                }
                slotNotAvailable = 0;
            }
        }
        index = nextSlotAvailable(appoints, maxAppointments);        
        appoints[index].date = date;        
        appoints[index].time = time;        
        appoints[index].patientNumber = patientNumber;        
        printf("\n*** Appointment scheduled! ***\n\n");
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
    return;
}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appoints, int maxAppointments, struct Patient* patients, int maxPatients)
{
    struct Date date;
    int index, patientNumber, lastDay = 0, appointIndex;
    printf("Patient Number: ");
    patientNumber = inputIntPositive();    
    index = findPatientIndexByPatientNum(patientNumber, patients, maxPatients);
    clearInputBuffer();
    if (index >= 0)
    {
        printf("Year        : ");
        date.year = inputIntPositive();
        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);
        printf("Day (1-");
        if (date.year % 4 == 0 && date.month == 2)
        {
            lastDay = 29;
        }
        else if (date.month == 2)
        {
            lastDay = 28;
        }
        else if (date.month == 4 || date.month == 9 || date.month == 11)
        {
            lastDay = 30;
        }
        printf("%d)  : ", lastDay);
        date.day = inputIntRange(1, lastDay);
        appointIndex = validAppointment(patientNumber, date, appoints, maxAppointments);
        if (appointIndex >= 0)
        {
            printf("\n");
            displayPatientData(&patients[index], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");
            if (inputCharOption("yn") == 'y')
            {
                appoints[appointIndex].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            }
            else
            {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber;
    int patientIndex;
    printf("\n");
    printf("Search by patient number: ");
    patientNumber = inputInt();
    printf("\n");

    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (patientIndex != -1)
    {
        displayPatientData(&patient[patientIndex], FMT_FORM);
        printf("\n");
    }
    else
    {
        printf("*** No records found ***\n\n");
    }

    suspend();
    searchPatientData(patient, max);
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNumber[PHONE_LEN + 1];
    int foundMatches = 0;
    int i = 0;
    printf("\nSearch by phone number: ");
    inputCString(phoneNumber, PHONE_LEN, PHONE_LEN + 1);
    printf("\n");

    displayPatientTableHeader();
    for (i = 0; i < max; ++i)
    {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            foundMatches = 1;
        }
    }
    if (foundMatches != 1)
    {
        printf("\n*** No records found ***\n");
    }
    printf("\n");
    suspend();
    searchPatientData(patient, max);
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int maxPatientNumber = 0;
    int i = 0;
    for (i = 0; i < max; ++i)
    {
        if (patient[i].patientNumber > maxPatientNumber)
        {
            maxPatientNumber = patient[i].patientNumber;
        }
    }

    return maxPatientNumber + 1;
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i;
    for (i = 0; i < max; ++i)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            return i;
        }
    }
    return -1;
}

// Checks to see whether a time slot is available
int timeSlotAvailable(struct Date date, struct Time time, struct Appointment* appoints, int maxAppointments)
{
    int i, slotAvailable = 0;    
    for (i = 0; i < maxAppointments; i++)
    {
        if (date.year == appoints[i].date.year && date.month == appoints[i].date.month && date.day == appoints[i].date.day && time.hour == appoints[i].time.hour && time.min == appoints[i].time.min)
        {            
            slotAvailable = 1;        
        }    
    }    
    return slotAvailable;
}

// Checks to see which is the next slot that is available and return the index
int nextSlotAvailable(struct Appointment* appoints, int maxAppointments)
{
    int i = 0, available = 0;    
    while (available == 0 && i < maxAppointments) 
    { 
        if (appoints[i].patientNumber < 1)
        {
            available = 1; 
        }        
        i++;
    }
    return i;
}

// Checks to see if an appointment is valid
int validAppointment(int patientNumber, struct Date date, struct Appointment* appoints, int maxAppointments)
{
    int i = 0, valid = 0;    
    while (valid == 0 && i < maxAppointments) 
    { 
        if ((appoints[i].patientNumber == patientNumber) && (appoints[i].date.day == date.day) && (appoints[i].date.month == date.month) && (appoints[i].date.year == date.year))
        { 
            valid = 1; 
        }        
        i++; 
    }    
    return i - 1;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");

    printf("Number: %05d\n", patient->patientNumber);

    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);

    printf("\n");
    inputPhoneData(&(patient->phone));
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int option;
    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");

    option = inputIntRange(1, 4);

    switch (option)
    {
    case 1:
        strcpy(phone->description, "CELL");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        phone->number[0] = '\0';
        printf("\n");
        return;
    }

    printf("\nContact: %s\n", phone->description);
    printf("Number : ");
    do
    {
        scanf("%s", phone->number);
        if (strlen(phone->number) != 10)
        {
            printf("Invalid 10-digit number! Number: ");
            clearInputBuffer();
        }
    } while (strlen(phone->number) != 10);

    printf("\n");
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int count = 0;
    FILE* file = fopen(datafile, "r");

    if (file != NULL)
    {
        while (count < max && fscanf(file, "%d|%14[^|]|%4[^|]|%19[^\n]",
                                      &patients[count].patientNumber,
                                      patients[count].name,
                                      patients[count].phone.description,
                                      patients[count].phone.number) != EOF)
        {
            ++count;
        }

        fclose(file);
    }
    else
    {
        printf("Error opening file: %s\n", datafile);
        count = -1;
    }
    return count;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int count = 0;
    FILE* file = fopen(datafile, "r");

    if (file != NULL)
    {
        while (count < max && fscanf(file, "%d,%d,%d,%d,%d,%d",
            &appoints[count].patientNumber,
            &appoints[count].date.year,
            &appoints[count].date.month,
            &appoints[count].date.day,
            &appoints[count].time.hour,
            &appoints[count].time.min) != EOF)
        {
            ++count;
        }

        fclose(file);
    }
    else
    {
        printf("Error opening file: %s\n", datafile);
        count = -1;
    }
    return count;
}