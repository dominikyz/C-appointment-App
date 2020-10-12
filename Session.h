//
//  Session.h
//
// Viktor Tatarenko , CO SCI 840, assignment 3 


#include <iostream>
#include <typeinfo>
#include <iomanip>
using namespace std;

#ifndef Session_h
#define Session_h

class Date
{
private:
    int day, month, year;
public:
    Date(int = 1, int = 1, int = 1900);
    void set(int = 1, int = 1, int = 1900);
    void get();
    void print() const;
    bool operator==(const Date &) const;
};

class Time
{
private:
    int hour, minute;
public:
    Time(int = 0, int = 0);
    void set(int = 0, int = 0);
    void get();
    void print() const;
    int get_hour() const;
    int get_minute() const;
    Time operator-(const Time &) const; // returns the difference of two Time objects
    bool operator==(const Time &) const; // compares two Time objects and returns True if first < second
    bool operator<(const Time &) const; // compares two Time objects and returns True if first < second
    bool operator>(const Time &) const; // compares two Time objects and returns True if first > second
};

class Appointment
{
protected:
    Date date;
    Time start_time, end_time;
    char description[40], location[40];
public:
    Appointment();
    virtual void read();
    virtual void print() const;
    Date get_date() const;
    Time get_start_time() const;
    Time get_end_time() const;
};


class Session : public Appointment
{
protected:
    char  client_id[11];
    char  fname[21];
    char  lname[21];
    float  hourly_charge;
    float total_charge;
public:
    Session(char client_id[11] = 0,char fname[21] = 0,char lname[21] = 0,float hourly_charge = 0.0);
    void set(char client_id[11] = 0,char fname[21] = 0,char lname[21] = 0,float hourly_charge = 0.0);
    void read();
    void print() const;
    char * get_id();
    char * get_fname();
    char * get_lname();
    float get_charge();
    ~Session();
};

Date::Date(int d, int m, int y)
{
    set(d, m, y);
}

void Date::set(int d, int m, int y)
{
    if (d >= 1 && d <= 31)
        day = d;
    else
    {
        cout << "\ninvalid day";
        cout << "\nPress any key to continue";
        system("pause");
        exit(1);
    }
    if (m >= 1 && m <= 12)
        month = m;
    else
    {
        cout << "\ninvalid month";
        cout << "\nPress any key to continue";
        system("pause");
        exit(1);
    }
    if (y >= 1900 && y <= 3000)
        year = y;
    else
    {
        cout << "\ninvalid year";
        cout << "\nPress any key to continue";
        system("pause");
        exit(1);
    }
}

void Date::get()
{
    char ch;
    
    cout << "Enter date in mm/dd/yyyy format: ";
    cin >> month >> ch >> day >> ch >> year;
    
    while (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 3000)
    {
        cout << "\nInvalid date entered" << endl;
        cout << "\nEnter date in mm/dd/yyyy format: ";
        cin >> day >> ch >> month >> ch >> year;
    }
}

void Date::print() const
{
    cout << day << "/" << month << "/" << year;
}

bool Date::operator==(const Date &d) const
{
    return day == d.day && month == d.month && year == d.year;
}

Time::Time(int h, int m)
{
    set(h, m);
}

void Time::set(int h, int m)
{
    if (h >= 0 && h <= 24)
        hour = h;
    else
    {
        cout << "\nInvalid hour";
        cout << "\nPress any key to continue";
        system("pause");
        exit(1);
    }
    
    if (m >= 0 && m <= 60)
        minute = m;
    else
    {
        cout << "\nInvalid minute";
        cout << "\nPress any key to continue";
        system("pause");
        exit(1);
    }
}

void Time::get()
{
    char ch;
    
    cout << "Enter time in military [hour:minute] format: ";
    cin >> hour >> ch >> minute;
    
    while (hour < 0 || hour > 24 || minute < 0 || minute > 60)
    {
        cout << "\nInvalid time entered";
        cout << "\nEnter time in military [hour:minute] format: ";
        cin >> hour >> ch >> minute;
    }
}

void Time::print() const
{
    cout << hour << ":" << minute;
}

int Time::get_hour() const
{
    return hour;
}

int Time::get_minute() const
{
    return minute;
}

Time Time::operator-(const Time &t) const
{
    if (minute >= t.minute)   // check minutes before creating the temp object
        return Time(hour - t.hour, minute - t.minute);
    else
        return Time(hour - t.hour - 1, minute + 60 - t.minute);
}

bool Time::operator==(const Time &t) const
{
    return hour == t.hour && minute == t.minute;
}

bool Time::operator<(const Time &t) const
{
    if (hour < t.hour)
        return true;
    else if ((hour == t.hour) && (minute < t.minute))
        return true;
    else
        return false;
}

bool Time::operator>(const Time &t) const
{
    return !(*this == t) && !(*this < t); // if not equal and not less, it must be greater
}

Appointment::Appointment() : date(), start_time(), end_time()
{
    strcpy(description, "");
    strcpy(location, "");
}

void Appointment::read()
{
    char c;
    
    date.get();
    
    do
    {
        cout << "Start time - ";
        start_time.get();
        
        cin.ignore(20, '\n');
        
        cout << "End time - ";
        end_time.get();
        
        cin.ignore(20, '\n');
        
        if (start_time.get_hour() > end_time.get_hour())
            cout << "\nEnd time cannot be earlier than start time" << endl;
        
    } while (start_time.get_hour() > end_time.get_hour());
    
    cout << "Enter description: ";
    int i = 0;
    cin.get(c);
    while (c != '\n')
    {
        description[i++] = c;
        cin.get(c);
    }
    description[i] = '\0';
    
    cout << "Enter location: ";
    i = 0;
    cin.get(c);
    while (c != '\n')
    {
        location[i++] = c;
        cin.get(c);
    }
    location[i] = '\0';
}

void Appointment::print() const
{
    cout << "\nAppointment Date: ";
    date.print();
    cout << "\nStart time: ";
    start_time.print();
    cout << "\nEnd time: ";
    end_time.print();
    cout << "\nDescription: " << description;
    cout << "\nLocation: " << location;
}

Date Appointment::get_date() const
{
    return date;
}

Time Appointment::get_start_time() const
{
    return start_time;
}

Time Appointment::get_end_time() const
{
    return end_time;
}


bool conflict(Appointment *, Appointment *[], int, int&); // params: Appt *, Appt *[], array size and index of Appt with conflict

int select_appt(Appointment *[], int);

enum classType { appt, session };

Session::Session(char client_id[11],char fname[21],char lname[21],float hourly_charge)
{
    set(client_id, fname, lname, hourly_charge);
}

void Session::set(char client_id[11],char fname[21],char lname[21],float hourly_charge)
{
  
    client_id = get_id();
    fname = get_fname();
    lname = get_lname();
    hourly_charge = hourly_charge;
}

void Session::read()
{
    char c;
    date.get();
    
    do
    {
        cout << "Start time - ";
        start_time.get();
        
        cin.ignore(20, '\n');
        
        cout << "End time - ";
        end_time.get();
        
        cin.ignore(20, '\n');
        
        if (start_time.get_hour() > end_time.get_hour())
            cout << "\nEnd time cannot be earlier than start time" << endl;
        
    } while (start_time.get_hour() > end_time.get_hour());
    
    cout << "Enter description: ";
    int i = 0;
    cin.get(c);
    while (c != '\n')
    {
        description[i++] = c;
        cin.get(c);
    }
    description[i] = '\0';
    
    cout << "Enter location: ";
    i = 0;
    cin.get(c);
    while (c != '\n')
    {
        location[i++] = c;
        cin.get(c);
    }
    location[i] = '\0';
    cout << "Enter client_id: ";
    i = 0;
    cin.get(c);
    while (c != '\n')
    {
        client_id[i++] = c;
        cin.get(c);
    }
    client_id[i] = '\0';
    cout << "Enter client first name: ";
    i = 0;
    cin.get(c);
    while (c != '\n')
    {
        fname[i++] = c;
        cin.get(c);
    }
    fname[i] = '\0';
    cout << "Enter client last name: ";
    i = 0;
    cin.get(c);
    while (c != '\n')
    {
        lname[i++] = c;
        cin.get(c);
    }
    lname[i] = '\0';
    cout << "Enter hourly charge: ";
    cin >> hourly_charge;
    
    total_charge = get_charge();
}

void Session::print() const
{
    cout << "\nSession Date: ";
    date.print();
    cout << "\nStart time: ";
    start_time.print();
    cout << "\nEnd time: ";
    end_time.print();
    cout << "\nDescription: " << description;
    cout << "\nLocation: " << location;
    cout << "\nClient First Name: " << fname ;
    cout << "\nClient Last Name: " << lname;
    cout << "\nCharges: " << total_charge;
}

 char * Session::get_id()
{
    return client_id;
}

 char * Session::get_fname()
{
    return fname;
}

 char * Session::get_lname()
{
    return lname;
}

float Session::get_charge()
{
    float charge ;
    float hr, min, total_time;
    Time start = get_start_time();
    Time end = get_end_time();
    hr = end.get_hour() - start.get_hour();
    min = end.get_minute() - start.get_minute();
    total_time = (hr + min/60);
    charge = hourly_charge * total_time;
    return charge;
};

Session::~Session()
{
}

#endif /* Session_h */
