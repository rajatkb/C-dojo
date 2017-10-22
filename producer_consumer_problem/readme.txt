./demo number_of_seconds_to_wait producer_count consumer_count

* may hault on extremely high numbers in windows BASH such as 
./demo 3 200 300
 # possibly due to print statements and internal threads scheduler taking the hit.