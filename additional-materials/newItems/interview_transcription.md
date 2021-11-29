## Trascription of Attardi interview about CMM

-------------------------------------------------------------------

[Interview to Giuseppe Attardi by Carlo Montangero about Customisable Memory Manager - conservative garbage collector for C++ developed for PoSSo (Polynomial System Solver) project (Pisa, 27 Nov 2021)](https://commons.wikimedia.org/wiki/File:Attardi_CMM_Interview.webm)

CM: Good morning Beppe and thank you for sharing your experience with the CMM, the Configurable Memory Management.

GA: Good morning Carlo. Hello and good morning to everybody.

CM: So the first question is: how did the project provides garbage collector for C++ stuff?

GA: The impetus came from Carlo Traverso, a mathematics, who was developing a project on a symbolic mathematics called POSSO.
At the time mathematicians were using LISP to build a symbolic algebra systems, for example, Maxima was built in LISP, but a commercial product called Mathematica just came about, which was written in C and it was promising to be faster and more efficient than the LISP.
And so, the mathematician said they wanted to also be efficient in their implementations.
I had been working on LISP and had built the ECL (Embeddable Common List), which is actually still in use and runs even on Blackberries now.
It's an implementational of common LISP that compiles to C and could achieve a similar speed performance, than native C.
Neverthless, mathematicians wants to have a C implementation. So I agree to work on the project on a condition: that I would have to build a garbage collector for C++. Otherwise I wouldn't be able to work. I mean, I was so used to have memory management that aren't released, that I could not work without it.

CM: So which were the major of design decisions for CMM.

GA: The main algorithm, of course was a solver for a polynomial equations, and working for stages where lots of tips were created that were no longer in use after the stage was completed.
So the idea was that the garbage collector could be customized to the algorithm itself.
So in this case, one could have a special temporary heap where the object will be allocated during each phase. And at the end of the phase, just the, the whole heap will be just discarded.
So in just one shot, all the memory would be collected very quickly.
That was the main ideas of the customizable collectors to have different heaps with different strategies for data collection.
Since this was to be embedded in a C environment, so we work with Tito Flagella, looking at a possible architecture that could be used in a garbage collector for C++.
And the idea that came about was to start with the approach that was proposed by Joel Bartlett, of Digital Equipment at the time: a kind of copying conservative garbage collector.

CM: What do you mean by conservative?

GA: Well, conservative means that, since the collector has to go through the C++ stack, where the variables are stored, and has to find that pointers too objects. As it's no way to know what data are on the stack of C++, and C++ doesn't provide this type information, the garbage collector has to do is assuming that anything that points to something, in a heap, is actually a pointer to an object, so it need to be followed and traced to find object, to be collected.
Since the algorithm doesn't know, it makes the conservative assumption that those are actually pointers, even though you might be not actually be pointers.
That means that some objects which are not being pointed by the heap might be still preserved. And then they are mantained maybe longer then the necessary, that's why they collected is called "conservative": it conserves a little bit more. It's a very unlikely situation situation, but it may happen.
So that's called conservative, because actually just preserves more than necessary so that it does not destroy anything that can be harmful.

CM: Okay. So did you fulfill your original targets?

GA: Yes. The idea of the customized collector was very helpful. I mean, in the POSSO, the B. algorith that's is polinomial solving algorith, was actually used effectively with the garbage collector. So the goal was perfectively fullfilled by the project.

CM: There were also some unforeseen developments or your work ?

GA: Yes. Once we build this garbage collector, it was a general design. So we decided to submit it to two conferences, like the USENIX conference, and, it turned out that, in Italy, I meat Bill Joy, which I knew before. Bill Joy is one of the designer and developer of a unix BSD 4.1, and he told me that he is one of the founder of sun Microsystems and that one of his colleagues, James Gosling, was working on a new programming language, in London, which was called Oak, which would have to work on all varieties of hardware and the needed to have a garbage collector that would work effectively and efficiently.
So I gave him a copy of the paper that I wrote about the CMS. And so we went back with the paper and in the paper there is a link to an FTP location where it could just download the code at the time. There wasn't the web at the time; you just FTP.
So the team started to download the code and they started to talk with us, asking questions about how to use it. And then eventually they used it in the development of the programming language, which turned out to be Java; for reasons of copyright, they couldn't use the name Oak so they had to change it to Java.
So what ended up is that our code ended up being part of the first implementation of Java. Later on, they built a different one, but the first release of their development were using our code.
When I presented the paper at the USENIX conference, I got compliments from Bjarne Stroustrup, a who is the designer of C++; he was always been against the use of garbage collector in C++ because he was afraid that it would reduce the efficiency of C++ as one of his design ideas for C++ where it should be as fast as possible with no overhead.
He liked the idea and my approach proved that it was really possible to have the best of both worlds. So you could have Garbage Collector with a custom heap. He claimed he had reasons to reconsider the idea of introduce a garbage collector to C++, and actually not only in C++, but in all languages that came after that.
Not just Java, Python, JavaScript and so on, all other scripting languages we use nowadays now are based on garbage collectors.
So CMM was basically the turning point where people started to consider the garbage collector as a useful activity, despite the bad idea that people had, that the garbage who had to be costly and expensive. The techniques that were developed at the time,  proved that you could do efficient garbage collectors. Could that have the benefit, the best of both worlds: efficiency and flexibility.

CM: Can you tell us also something about the way you develop CMM?

GA: Basically we where working in pairs, myself and Tito Flagella as developers. At the time arent version control systems a new system, like CVS and later some version that comes later, but, in order to keep our software easier to maintain we were as a feature, of EMACS, which allows you to do something that basically is a commit.
So just saying I'm committing the code and just as a command in EMACS, we just allow you to stage you are committing a version with a comment saying, what is the difference or the changes that were made, which are stored in the file.
So a very simple way to do it, but it was convenient.
And then we would, we would make releases and saving the tarballs of the directors. And so they'd give you the whole history of development.
So it was just kind of handmade system for versioning.

CM: And what about the hardware?

GA: At the time you were using the some workstation, which were among the most efficient and convenient hardware, you're running a UNIX, and then later we moved to the PCs with Linux.

CM: Thank you very much for your time and for your excellent explanation.

GAL Thank you for your interest. I think that open source is incredible opportunity for software developers and, and the community as an important aspect of this. Thank you for participating.
