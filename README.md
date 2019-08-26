# MAODV
Multiple Ad Hoc On-Demand Distance Vector Routing Algorithm

In this script, multiple paths have been explored using AODV algorithm. Basic AODV algorithm explores a single path between a source and a destination, whereas MAODV explores k possible paths between a source and a destination.
Firstly, a random undirected graph has been generated using generating_graph() function. Now, source and destination are given as inputs, and then the maodv() funtion is called.
The path is stored in a stack which is populated by calling the find_path() method.

1. find_path(a,b,c) : this method creates a request packet which will be send by the source and it contains data like source,destination,hop_cnt(edges travelled),seq_no(different assigned with each packet),flag(to distinguish betweeen paths), previous(to backtrack).Then this function passes this request packet to explore_path() function. It returns nothing.
2. explore_path(a) : this method is a recursive function which calls itself on certain conditions and terminates when the destination is reached.
2a. Firstly, node is marked as visited and the terminating condition is checked.
2b. If the condition is FALSE; then two signals are assigned named as pos_sig and neg_sig.
2c. Now, the path is searched in Route table; if the result is positive then the function search_route table returns false and we increments the pos_sig, otherwise we increment the neg_sig.
2d. Two, different cases are handled after that which calls the explore_path function again.

ThankYou for referring my code for multipath discovery using standard AODV.
