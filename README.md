# blist

Output a text file to stdout (for redirection) preceded by a header block identifying the file.

## Historic Note

This app and C++ code-base was originally created around 1992 - 1996 for use in a non-GUI UNIX environment,
 where a significant part of the development process involved pretty-printed code listing on a printer for peer-review & diagnostic archive purposes.

```shell script
blist file.* > lpr my-printer
``` 

For context, it is worth mentioning for younger readers that this was a time when: 
* the first C++ ISO standard did not even exist yet.
* the Standard Template Library (STL) had only just been released, and nobody was really using it in production environments yet due to "newness".
* each hardware system vendor (for example, NCR, Fujitsu, etc) shipped their own slightly different UNIX variant. 
* each UNIX environment shipped with their own C and C++ compilers, each with slightly different feature sets and bugs.
* Linux v1.0 had just been released, and was only used by hobbyists. 
* GCC was still at v2.x and not very widely used beyond Linux distros and universities.
* each software development shop had their own internal "smart string" class to encapsulate common reference-counting and/or memory management logic, to avoid common `char*` pointer manipulation bugs.

Yes, the C++ software world is _completely_ different (aka better!) today,
 with Linux GUI-based environments and IDE's everywhere!

Mostly the purpose of this repo is to work through upgrading this application code to use "Modern C++" (meaning primarily C++14/17 ISO standard features)
 to see how ~25 years of C++ language and core library enhancements have made things better for C++ developers.
