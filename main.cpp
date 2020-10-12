//
//  main.cpp
//
// Viktor Tatarenko , CO SCI 840, assignment 3


#include <iostream>
#include <typeinfo>
#include <iomanip>
#include "Session.h"

using namespace std;



int main()
{
    Appointment *ap[100], *temp;
    Session *sp;
    classType type[100];
    int choice, selection, count = 0, index, i;
    char id[11], fname[21], lname[21];
    Date date;
    float charges = 0.0;
    bool found;
    
    do
    {
        cout << "\n\nAppointment Management program by Viktor Tatarenko"
        << "\nChoose one of the following: "
        << "\n------------------------------"
        << "\n1. Create a new appointment"
        << "\n2. Create a new session"
        << "\n3. View all appointments and sessions"
        << "\n4. Edit appointment/session"
        << "\n5. Check a date for appointments/sessions"
        << "\n6. View sessions for a client"
        << "\n7. View charges for a client"
        << "\n8. View total charges for all clients"
        << "\n9. Delete an appointment or session"
        << "\n10. Quit"
        << "\n-----------------------------> ";
        
        cin >> choice;
        
        system("cls");
        
        switch (choice)
        {
            case 1:        temp = new Appointment;                 // create temp Appointment pointer
                temp->read();                         // read values into temp
                if (conflict(temp, ap, count, index)) // if there is a conflict with an existing Appointment
                {                                     // index will identify it
                    cout << "\nThis will conflict with: ";
                    ap[index]->print();     // print conflicting Appointment
                    cout << "\n\nAppointment not entered.";
                }
                else
                {
                    ap[count] = temp;
                    type[count] = appt; // parallel array is used to identify the type of object ptr stored in ap[]
                    count++;
                }
                break;
                
            case 2:        temp = new Session;                     // create temp Session pointer
                temp->read();                         // read values into temp
                if (conflict(temp, ap, count, index)) // if there is a conflict with an existing Session
                {                                     // index will identify it
                    cout << "\nThis will conflict with: ";
                    ap[index]->print();     // print conflicting Session
                    cout << "\n\nSession not entered.";
                }
                else
                {
                    ap[count] = temp; // store Sessions in both arrays because when searching for Session info
                    type[count] = session; //parallel array is used to identify the type of object ptr stored in ap[]
                    count++;
                }
                break;
                
            case 3:        for (i = 0; i < count; i++)
            {
                ap[i]->print();
                cout << endl;
            }
                break;
                
            case 4:        if ((choice = select_appt(ap, count)) == -1) // Specified date could not be found
            {
                cout << "\nThere are no appointments or sessions on this date.";
                break;
            }
            else
            {
                temp = ap[choice];                    // save the pointer to the Appt. or Session to be deleted.
                
                if (choice < count - 1)                // if the one being deleted is not the last in the array
                    for (i = choice; i < count; i++) // shift all Appt pointers into lower-index place in array
                    {
                        ap[i - 1] = ap[i];
                        type[i - 1] = type[i];
                    }
                
                count--;
            }
                
                do
                {
                    cout << "\nEnter 1 to select an appointment and 2 to choose a session: ";
                    cin >> selection;
                    
                    if (selection == 1)
                    {
                        ap[count] = new Appointment;
                        type[count] = appt; //parallel array is used to identify the type of object ptr stored in ap[]
                    }
                    else if (selection == 2)                     // if the new one is a Session
                    {
                        ap[count] = new Session;
                        type[count] = session; //parallel array is used to identify the type of object ptr stored in ap[]
                    }
                    
                } while (selection < 1 || selection > 2);
                
                ap[count]->read();    // enter values into newly created object but don't increment count until verified
                
                if (conflict(ap[count], ap, count, index)) // if conflicts with an existing Appoint or Session
                {                                          // index will identify conflicting Appt or Session
                    cout << "\nThis will conflict with:\n";
                    ap[index]->print();                  // print conflicting appt or session
                    cout << "\n\nAppointment or session not modified.";
                    
                    delete ap[count];   // delete the one added
                    ap[count++] = temp; // copy temp back into ap
                }
                else
                    count++; // no conflict so count the last one just added - count was not incremented until now.
                
                break;
                
            case 5:        cout << "\nEnter date to check: ";
                date.get();
                
                found = false;
                for (i = 0; i < count; i++)
                    if (date == ap[i]->get_date())
                    {
                        found = true;
                        ap[i]->print();
                        cout << endl;
                    }
                
                if (!found)
                {
                    cout << "\nYou have no appointments or sessions on ";
                    date.print();
                }
                
                break;
                
            case 6:        do
            {
                cout << "\nEnter 1 to search by I.D. or 2 to search by name: ";
                cin >> choice;
                found = false;
                
                if (choice == 1)
                {
                    cout << "\nEnter client I.D.: ";
                    cin >> id;
                    
                    for (i = 0; i < count; i++)
                        if (type[i] == session)
                        {
                            sp = (Session*)(ap[i]);
                            if (!strcmp(id, sp->get_id())) // we have to look at Sessions only
                            {
                                sp->print();
                                found = true;         // because Appts don't have get_id()
                            }
                        }
                    
                    if (!found)
                        cout << "\nClient not found. ";
                }
                else if (choice == 2)
                {
                    cout << "\nEnter client last name: ";
                    cin >> lname;
                    
                    cout << "\nEnter client first name: ";
                    cin >> fname;
                    
                    for (i = 0; i < count; i++)
                        if (type[i] == session)
                        {
                            sp = (Session*)(ap[i]);
                            if (!strcmp(lname, sp->get_lname()) && !strcmp(fname, sp->get_fname()))
                            {
                                sp->print();
                                found = true;
                            }
                        }
                    
                    if (!found)
                        cout << "\nClient not found. ";
                }
                else
                    cout << "\nPlease, enter either 1 or 2: ";
                
            } while (choice < 1 || choice > 2);
                
                break;
                
            case 7:        charges = 0.0;
                found = false;
                
                do
                {
                    cout << "\nEnter 1 to search by I.D. or 2 to search by name: ";
                    cin >> choice;
                    if (choice == 1)
                    {
                        cout << "\nEnter client I.D.: ";
                        cin >> id;
                        for (i = 0; i < count; i++)
                            if (type[i] == session)
                            {
                                sp = (Session*)(ap[i]);
                                if (!strcmp(id, sp->get_id()))
                                {
                                    found = true;
                                    charges += sp->get_charge();
                                    cout << "\nCharges for " << id << " is: " << charges;
                                }
                            }
                        
                        if (!found)
                            cout << "\nClient not found. ";
                    }
                    else if (choice == 2)
                    {
                        cout << "\nEnter client last name: ";
                        cin >> lname;
                        
                        cout << "\nEnter client first name: ";
                        cin >> fname;
                        
                        for (i = 0; i < count; i++)
                        {
                            if (type[i] == session)
                            {
                                sp = (Session*)(ap[i]);
                                if (!strcmp(lname, sp->get_lname()) && !strcmp(fname, sp->get_fname()))
                                {
                                    found = true;
                                    charges += sp->get_charge();
                                    cout << "\nCharges for " << fname << " " << lname << " is: " << charges;
                                }
                            }
                        }
                        if (!found)
                            cout << "\nClient not found. ";
                    }
                    else
                        cout << "\nPlease, enter either 1 or 2: ";
                    
                } while (choice < 1 || choice > 2);
                
                break;
                
            case 8:        charges = 0.0;
                
                for (i = 0; i < count; i++)
                    if (type[i] == session)
                    {
                        sp = (Session*)(ap[i]);
                        charges += sp->get_charge();
                    }
                
                cout << "\nTotal charges for all clients is " << charges;
                
                charges = 0.0;
                break;
                
            case 9:        if ((index = select_appt(ap, count)) == -1)  // Specified date could not be found
            {
                cout << "\nThere are no appointments or sessions on this date.";
                break;
            }
                
            else if (index < count - 1)        // if the one being deleted is not the last in the array
                for (int i = index; i < count - 1; i++) //shift all Appointment objects into lower-index place in array
                    (*(ap[i])) = (*(ap[i + 1]));
            else
                delete ap[count - 1]; // delete last Array element
                
                count--;
                
                break;
                
            case 10:    return 0;
                
            default:    cout << "\nInvalid entry - please, enter a number between 1 and 10.";
        }
    } while (1);
}

bool conflict(Appointment *p, Appointment *ap[], int size, int& i) // i is the index of the array element with conflict
{                                                                   // the function modifies i so the caller can get it
    Date date = p->get_date();
    Time start = p->get_start_time();
    Time end = p->get_end_time();
    
    for (i = 0; i < size; i++)
        if (date == ap[i]->get_date())
            if ((start == ap[i]->get_start_time()) ||
                ((start < ap[i]->get_start_time()) && (end > ap[i]->get_start_time())) ||
                ((start > ap[i]->get_start_time()) && (start < ap[i]->get_end_time())))
                return true;
    return false;
}

int select_appt(Appointment *ap[], int size) // returns the index of the array element if found and -1 if not found
{
    Date date;
    int choice, int_array[10];
    
    cout << "\nEnter appointment or session date: ";
    date.get();
    
    for (int i = 0, j = 0; i < size; i++) // search for given date
        if (date == ap[i]->get_date())
        {
            int_array[j++] = i; // Store i in int_array when date matches
            cout << "\n----------- " << j << " ----------";
            ap[i]->print();
            cout << endl;
            
            
            if (j == 0) // if Appt or Session not found
                return -1;
        }
    
        else // Appt or Session found
        {
            do
            {
                cout << "\nSelect the appointment by entering its number: [1 - " << j << "]: ";
                cin >> choice;
            } while (choice < 1 || choice > j);
            
            return int_array[choice - 1];
        }
    return 0;
}


