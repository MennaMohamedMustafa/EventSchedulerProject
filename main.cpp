#include <iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include <ctime>
#include <Windows.h>
using namespace std;
class Event
{
public:
    ifstream inewevent;
    ofstream onewevent, temp;
    string name, StartDate, EndDate, place, startTime, Reminder;
    vector <string> details;
    map < string, vector<string> > event;
    map < string, vector<string> > ::iterator it;

    void update_file()
    {
        ifstream UpdateEvent("Eventschedule.txt");
        ofstream temp("temp.txt");

        for (it = event.begin(); it != event.end(); ++it)
        {
            temp << it->second[0] << "\t"  << it->second[1] << "\t" <<it->first <<"\t"<< it->second[2] << "\t" << it->second[3] << "\t" << it->second[4] << endl;
        }
        temp.close();
        UpdateEvent.close();
        remove("Eventschedule.txt");
        rename("temp.txt", "Eventschedule.txt");
    }
    void update_map()
    {
        inewevent.open("Eventschedule.txt", ios::in | ios::app);
        while (!inewevent.eof())
        {
            inewevent >> name >>  place >> StartDate >> EndDate >> startTime >> Reminder;
            event[StartDate].push_back(name);
            event[StartDate].push_back(place);
            event[StartDate].push_back(EndDate);
            event[StartDate].push_back(startTime);
            event[StartDate].push_back(Reminder);
        }
        inewevent.close();
    }
    void show()
    {

        for (it = event.begin(); it != event.end(); ++it)
        {
            cout<<"The Name of the event      :"<<it->second[0]<<endl;
            cout<<"The StartDate of the event :"<<it->first    <<endl;
            cout<<"The place of the event     :"<<it->second[1]<<endl;
            cout<<"The EndDate of the event   :"<<it->second[2]<<endl;
            cout<<"The StartTime of the event :"<<it->second[3]<<endl;
            cout<<"The Reminder of the event  :"<<it->second[4]<<endl;
            cout<<endl;
        }
    }
    void update_event()
	{
		cout << "Enter the StartDate of event you want update" << endl;
		cin >> StartDate;
		if (event.find(StartDate) != event.end())
		{
			it = event.find(StartDate);
			cout << "The details of the event you want to update    " << endl;
			cout << endl;
			cout << "name:" << it->second[0] << "  " << "place:" << it->second[1] << "  " << "EndDate:" << it->second[2] << "  " << "StartTime:" << it->second[3] << "  " << "Reminder:" << it->second[4] << endl;
			cout << endl;
			cout << "Enter the details of the event you want to update" << endl;
			cout << endl;
			cout << "Enter the event's new name : ";
			getline(cin.ignore(), name);
			//cin >> name;
			cout << endl << "Enter the event's new place : ";
			 getline(cin, place);
			//cin >> place;
			cout << endl << "Enter the event's new  EndDate : ";
			getline(cin, EndDate);
			//cin >> EndDate;
			cout << endl << "Enter the event's new StartTime : ";
			getline(cin, startTime);
			//cin >> startTime;
			cout << endl << "Enter the event's new Reminder : ";
			getline(cin, Reminder);
			//cin >> Reminder;
			if (intersect(StartDate, EndDate) == false)
			{
				cout << endl << "sorry this event can't be saved as it intersects with another Event !!!" << endl;
			}
			else
			{
				it->second[0] = name;
				it->second[1] = place;
				it->second[2] = EndDate;
				it->second[3] = startTime;
				it->second[4] = Reminder;
			}
		}
		else
		{
			cout << "this event isn't found" << endl;
		}
	}
    void delete_event()
    {
        cout << " please enter the StartDate for the event you want to delete : ";
        cin >> StartDate;
        if (event.find(StartDate) != event.end())
        {
            event.erase(StartDate);
            cout<<"The event has been deleted !"<<endl;
        }
        else
        {
            cout << " Event already not exist :/ @#$ " << endl;
        }
    }
    bool intersect(string Start, string End)
    {
        for (it = event.begin(); it != event.end(); ++it)
        {
            if ((Start > it->first && End > it->first) || (Start < it->second[2] && End < it->second[2]))
            {
                continue;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
    void add_event()
    {
        onewevent.open("Eventschedule.txt", ios::out | ios::app);
        cout <<  "Enter the details of the event you want to add"<<endl;
        cout<<endl;
        cout << "Enter the event's name : " ;
        getline(cin.ignore(), name);
        cout << endl<< "Enter the event's place : "  ;
        getline(cin, place);
        cout << endl<< "Enter the event's StartDate : " ;
        getline(cin, StartDate);
        cout << endl<< "Enter the event's  EndDate : " ;
        getline(cin, EndDate);
        cout << endl<< "Enter the event's StartTime : " ;
        getline(cin, startTime);
        cout << endl<< "Enter the event's Reminder : " ;
        getline(cin, Reminder);
        if (intersect(StartDate, EndDate)==true)
        {
            cout << endl << "sorry this event can't be saved as it intersects with another Event  ." << endl;
        }
        else
        {
            onewevent << name << "\t" << place << "\t" << StartDate << "\t" << EndDate << "\t" << startTime << "\t" << Reminder << endl;
            onewevent.close();
            update_map();
        }
        onewevent.close();
    }
    void reminder()
    {
        string word;
        word="you have an event you would like you attend";
        int remind_day;
        int remind_time;
        int rem;
        int st;
        time_t now = time(0);
        tm*ltm = localtime(&now);
        remind_day=ltm->tm_mday ;
        remind_time=ltm->tm_hour ;
        for (it=event.begin(); it!=event.end(); it++)
        {
            StartDate=it->first;
            Reminder=it->second[4];
            stringstream Rs(Reminder);
            stringstream Sss(StartDate);
            Rs>>rem;
            Sss>>st;
            if(remind_day==st&& remind_time==rem)
            {
                cout<<word<<endl;
                break;
            }
        }
    }
    void welcome()
    {
        cout<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"\t\t\t*  *  *  *  *  *  *  *  *  *  *  *  * "<<endl;
        cout<<"\t\t\t*       ~  Event scheduler  ~       * "<<endl;
        cout<<"\t\t\t*                                   * "<<endl;
        cout<<"\t\t\t* 1) Add new Event                  * "<<endl;
        cout<<"\t\t\t* 2) Display All Events             * "<<endl;
        cout<<"\t\t\t* 3) Update an Event                * "<<endl;
        cout<<"\t\t\t* 4) Delete an Event                * "<<endl;
        cout<<"\t\t\t* 5) Exit                           * "<<endl;
        cout<<"\t\t\t*                                   * "<<endl;
        cout<<"\t\t\t* Enter UR Choice :                 * "<<endl;
        cout<<"\t\t\t*  *  *  *  *  *  *  *  *  *  *  *  * "<<endl;
        cout<<endl;
        cout<<endl;
        reminder();
    }
    void Operations()
    {
        while (true)
        {
            welcome();
            update_map();
            int choice;
            cin>>choice;
            system("cls");
            if(choice==1)
            {
                add_event();

            }
            else if(choice==2)
            {
                show();

            }
            else if(choice==3)
            {
                update_event();
                update_file();
            }
            else if(choice==4)
            {
                delete_event();

            }
            else if(choice==5)
            {
                exit(0);
            }
             update_file();
             system("pause");
             system("cls");
        }
    }
};
int main()
{
    Event E;
    E.update_map();
    E.Operations();
    E.update_file();

    return 0;
}





