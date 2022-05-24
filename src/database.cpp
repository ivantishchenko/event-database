#include "database.h"

#include <utility>
#include <algorithm>
#include <iterator>

void Database::Add(const Date& date, const string& event) {
    lookup_map_[date].insert(event);
    order_map_[date].push_back(event);
}

void Database::Print(ostream& out) const {
    for(const auto& [date, event_set]: lookup_map_) {
        for(const auto& event: event_set) {
            out << date << ' ' << event << endl;
        }
    }
}
void Database::Print() const {
    Print(cout);
}

pair<Date, string> Database::Last(const Date& date) const {
    auto upper_bound_it = lookup_map_.upper_bound(date);
    if(upper_bound_it == begin(lookup_map_)) {
        throw invalid_argument("No entries");
    }
    upper_bound_it = prev(upper_bound_it);
    
    Date last_date = upper_bound_it->first;
    string last_event = order_map_.at(last_date).back();

    return make_pair(last_date, last_event);
}

map<Date, set<string>> Database::GetLookupMap() const {
    return lookup_map_;
}

ostream& operator<<(ostream& out, const Database& db) {
    db.Print(out);
    return out;
}