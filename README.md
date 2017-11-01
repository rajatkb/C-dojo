# C-dojo
  Its collection of C scripts that i have written. Few nifty tricks or usable functions here and there.

# 1. 2-d Array using linked list
  No reason to have this implementation. But just for the purpose of having one

# 2. Generators in C
  Wanted something that looks like yield of python in C so hence the small script

# 3. Scheduler in C
  An actual version for multiprocess management is on its way. Intend to make a server out of it.
  But ya this is a complete working version of scheduling using linked list.
  You can add more and more data into the accounting data including IO burst times
  It is just a simulation for anyone to compare. Nothing else althout the header files are usable i.e 
  Schedule.h and process.h which decsribes the shcedulers and the process structures and functions
  Also round robin is not using a circular qeue simply returns the first node on facing a null i.e end of list

# 4. Producer_Consumer
  Nothing much. Just class assignment in C. It schedules many producer and consumer threads at once and runs them all for specified time
  
  $ ./demo execution_time producer_thread_count consumer_thread_count

# 5. BATMAN : Bidrectional Autonomous Trolley Manager
  This one is a poorly implemented variant of the problem. Reason being. There is no deadlock resolution mechanism. And I have simply       assumed there is a deadlock when all the trolleys are entering at once. Also, the problem statement describes that there must be only     one BAT thread executing or crossing at a time. But why ? The image provided gives a different story all together. NO IDEA !!! If some     one out there can help me in deadlock identification and a resolution routine please do. The current implementation also does not uses     the right first notion for all threads, will implement it soon. 
