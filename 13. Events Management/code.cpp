#include <bits/stdc++.h>
using namespace std;

class Event
{
    public:

    int startTime;
    int endTime;

    virtual double calculateProfit() =0;

    virtual void takeinput() =0;

    friend istream& operator>>(istream& inp, Event* event)
    {
        event->takeinput();
        return inp;
    }

};

class  Concert: public Event
{
    public:

    int ticketPrice;
    int ticketsSold;
    int artistFee;
    int logisticCost;

    double calculateProfit()
    {
        double ticketRevenue = ticketPrice*ticketsSold;
        double netRevenue = (0.82) * ticketRevenue;

        double cost = artistFee + logisticCost;
        double profit = netRevenue - cost;

        double netProfit;
        
        if (profit > 2*cost)
        {
            netProfit = 0.7*profit;
        }
        else
        {
            netProfit = profit;
        }

        return netProfit;
    }

    void takeinput()
    {
        cin >> startTime >> endTime >> ticketPrice >> ticketsSold >> artistFee >> logisticCost;
    }

};

class  TheaterShow: public Event
{
    public:

    int baseTicketPrice;
    int totalSeats;
    int venueCost;

    double calculateProfit()
    {
        double ticketRevenue = 0.25*totalSeats*(2*baseTicketPrice) + 0.75*totalSeats*baseTicketPrice;
        double netRevenue = (0.82)*ticketRevenue;

        double popcornRevenue = 0.25*totalSeats*150;
        double netProfit = netRevenue + popcornRevenue - venueCost;

        return netProfit;
    }

    void takeinput()
    {
        cin >> startTime >> endTime >> baseTicketPrice >> totalSeats >> venueCost;
    }


};

class  Wedding: public Event
{
    public:

    int baseAmount;
    int decorationCost;
    int guestCount;
    int venueCost;

    double calculateProfit()
    {   
        double totalVenueCost;
        double cateringCost;

        // for venuecost
        if (guestCount > 200)
        {
            totalVenueCost = 3*venueCost;
        }
        else
        {
            totalVenueCost = venueCost;
        }

        // for catering cost
        if (guestCount > 100)
        {
            cateringCost = guestCount*70;
        }
        else
        {
            cateringCost = guestCount*100;
        }

        double netprofit = baseAmount - totalVenueCost - decorationCost - cateringCost;
        
        return netprofit;
    }

    void takeinput()
    {
        cin >> startTime >> endTime >> baseAmount >> decorationCost >> guestCount >> venueCost;
    }


};
class customcomp
{
    public:

    bool operator()(Event *e1, Event *e2)
    {
        return e1->endTime < e2->endTime;
    }

};


class EventScheduler
{
    public:

    int n;
    vector <Event*> listOfEvents;
    EventScheduler(int n1): n(n1){};


    
    void solve()
    {
        std::sort(listOfEvents.begin(), listOfEvents.end(), customcomp());
        vector< int >prev(n,-1);

        prev[0] =0;


        for (int i = 0; i < n; i++)
        {

            bool flag = false;
            for (int j = i; j >=0; j--)
            {
                if(listOfEvents[i]->startTime >= listOfEvents[j]->endTime)
                {   
                    if(!flag)
                    {
                        prev[i] =j; flag = true;
                    }

                }
            }
        }

        vector <double> dp(n);
        dp[0] =  listOfEvents[0]->calculateProfit();

        for (int i = 1; i < n; i++)
        {

            double max_profit = dp[i-1];

            if (prev[i]>=0)
            {
                if (max_profit < dp[prev[i]] + listOfEvents[i]->calculateProfit())
                {
                    max_profit = dp[prev[i]] + listOfEvents[i]->calculateProfit();
                }
            }
            else
            {
                if (max_profit < listOfEvents[i]->calculateProfit())
                {
                    max_profit = listOfEvents[i]->calculateProfit();
                }
            }

            dp[i] = max_profit;
        }

            double  maxi =  *max_element(dp.begin(), dp.end());

            cout << fixed << setprecision(2) << maxi <<'\n';
    }   

};


int main()
{   

    int no_of_events;
    cin >> no_of_events;
    
     EventScheduler eventSched(no_of_events);

    for (int i = 0; i < no_of_events; i++)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            Event *e = new Concert;
            cin >> e;
            eventSched.listOfEvents.push_back(e);
        }
        else if (type == 2)
        {
            Event *e = new TheaterShow;
            cin >> e;
            eventSched.listOfEvents.push_back(e);
        }
        else
        {
            Event *e = new Wedding;
            cin >> e;
            eventSched.listOfEvents.push_back(e);
        }
    }

    eventSched.solve();
}
