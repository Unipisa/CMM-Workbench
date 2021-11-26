**Q: How did the project to write a garbage collector for C++ start?**

A: The initial impetus came from Carlo Traverso, then professor at the Department of Mathematics in Pisa, who wanted to implement a symbolic algebra system not only mathematically advanced, but also computationally efficient. Until then, such systems, like MIT's Macsyma were implemented in Lisp. Mathematica, a commercial product from Wolfram, written in C, had recently come out, promising greater efficiency. I had developed ECL, Embeddable Common Lisp, an implementation of Lisp in C, which compiled from Lisp to C. ECL was therefore able to achieve similar performance to algorithms written in C, provided that some type declarations for variables were added, which in Lisp are optional.

However, Carlo insisted on a solution in an imperative language, which could also be used by those who were not familiar with Lisp. I decided to comply with his request under two conditions: to use an object-oriented language, which I had been a great fan of since I met Alan Kay and his SmallTalk, and to have a garbage collector.

**Q: Which were the major design/development decision for CMM?**

A: In the CMM design phase, I got a lot of help from Tito Flagella, who among the various conservative garbage collection techniques, suggested that we base ourselves on Joel Bartlett's mostly-copying technique.

*Anche qualcosa sulla decisione di usare un VS fatto in casa, pf*

**Q: Did you fulfil the original target?**

A: *Rispetto a PoSSo, oltre a:*

When I presented CMM at the 1994 Usenix Conference, Bjarne Stroustrup, the inventor of C++, approached me and complimented me, saying that with this new technique, he could start thinking about introducing a GC into C++. The objection to the GC was that it might introduce overhead on language performance. Since CMM allows you to choose which objects to apply GC to, and also to specialize the algorithm for particular needs, this made it a viable solution.

**Q: There where unforeseen developments?**

A: An important role in the diffusion of CMM was played by Bill Joy, father of Unix BSD 4.1 and founder of Sun Microsystems.
During one of his trips to Italy, he told me about a project that James Gosling was developing, for a new language called Oak, which had to run on various devices and for which a sophisticated garbage collector was needed. I gave him a copy of the CMM article, which contained a link to download the code via FTP. Soon the Sun Engineering group began using it and writing to me for clarification.

The language was renamed Java, due to copyright issues over the term Oak.

When I met one of them at a conference in Cambridge, they told me that they were enthusiastic and that we were a couple of years ahead of them in developing a garbage collector. News of the use of CMM for Java spread through the community, and Paul Wilson, author of a comprehensive review on the subject, complimented me, because in that way, the GC technique was becoming main stream. In fact, almost every programming language developed in recent years incorporates a garbage collector.

**Q: Which development platform were you using?**

A: At that time, Sun workstations were used. Then, PCs running Linux.

**Q: In what sense is CMM conservative?**

A: A tracing collector has to discover all live objects in the heap, i.e. those that are supposedly still in use by the program. They  can be reached traversing any data structure refereed in the variables present in the stack, hence the collector has to go through the stack to identify such roots.
Unfortunately C++ does not provide run time type information to recognise the types of the objects on the stack.
Therefore a conservative collector has to scan the stack blindly, assuming that any value in a stack, a 64-bit value, does indeed represent a pointer to an object on the heap.
However it might misinterpret an integer or another data type as a pointer and follow it to get to an object in the heap, from which it will trace through its descendants.
The only harm this can do to the program, is to consider as still alive objects that are not. These object will be preserved from collection and therefore “conserved” longer than they should.
Hence the name conservative collector.
