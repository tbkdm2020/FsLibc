#ifndef STDIOFIXTURE_H
#define STDIOFIXTURE_H

#include "fslc_stdio.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <memory>

struct StdIOFixture
{
    FSLC_FILE stream;
    
    enum struct CalledFunc { None, PreOp, PutC, PostOp };
        
    struct FuncCallItem {
        enum CalledFunc opera;
        int param1;
        bool operator == (const FuncCallItem &other) const
        {
            return opera == other.opera 
                && param1 == other.param1;
        }
    };

    std::vector<FuncCallItem> FuncCallLog;
    
    int eof_counter;
    std::ostringstream ostring;
    
    std::istringstream istring;
    
    int fail_getc_calls;
    
    std::unique_ptr<char> expected_fstring;
    
    int eprintf(const char *format, ...);
    
    StdIOFixture();
    
    static int fixture_putc(int c, FSLC_FILE *stream);
    static void fixture_preop(FSLC_FILE *stream);
    static void fixture_postop(FSLC_FILE *stream);
    static int fixture_getc(FSLC_FILE *stream);
    static int fail_getc(FSLC_FILE *stream);
    
    static int null_putc(int c, FSLC_FILE *stream);
    static void null_prepostop(FSLC_FILE *stream);
};


std::ostream &operator<< (std::ostream &stream, const StdIOFixture::FuncCallItem &citem);


#endif // STDIOFIXTURE_H
