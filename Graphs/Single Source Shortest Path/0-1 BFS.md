IF the weights are 0 and 1 only

then you are paying O(VlogV) just to keep these d values sorted

that's overkill for sorting

instead push 0 weights to the front
        push 1 weights to the rear

in this way the Dijkstra queue is always sorted

so picking up the front value from the queue TRIGGERS the core lemma of Dijkstra "nodes are permanently locked in upon extraction"


If you manage to keep the queue sorted, you are done. That is the entire mathematical foundation.

(the queue) must strictly output the smallest distance next.