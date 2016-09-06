#define DEBUG 

#ifdef DEBUG
    #define RET_FALSE   ({\
           printf("return FALSE at line:%d.\n", __LINE__);\
            false;\
        })
    #define RET_TRUE    ({\
            printf("return TRUE at line:%d.\n", __LINE__);\
            true;\
        })
#else
    #define RET_FALSE   false
    #define RET_TRUE    true
#endif

#define SKIP_BLANK(p)   ({\
        while (' ' == *(p))\
            (p)++;\
    })
    
#define BLANK_OR_NULL(p)   ({\
        while (' ' == *(p))\
            (p)++;\
        (*(p))?(RET_FALSE):(RET_TRUE);\
    })

/* integer: "01" */    
#define SKIP_INTEGER(p, cnt)    ({\
        cnt = 0;\
        while (('0'<=*(p)) && ('9'>=*(p)))\
        {\
            (p)++;\
            (cnt)++;\
        }\
    })
    
/* flaot: "0.1" or "0." or ".1" or inter */
#define SKIP_FLOAT(p, cnt)    ({\
        if ('.' == *(p))\
        {\
            (p)++;\
            SKIP_INTEGER((p), (cnt));\
            if (cnt)    /* for such as ".0" or "12.12" */\
                (cnt) ++;\
        }\
        else\
        {\
            SKIP_INTEGER((p), (cnt));\
            if ((cnt) && ('.'==*(p)))\
            {/* for such as "12." or "12.12" */\
                (p)++;\
                unsigned int    cnt_t = 0;\
                SKIP_INTEGER((p), cnt_t);\
                (cnt) += cnt_t+1;\
            }\
        }\
    })
    
bool isNumber(char* s) 
{
    char            *p = s;
    unsigned int    cnt = 0;
    
    if (!p || (!*p))
        return RET_FALSE;
        
    SKIP_BLANK(p);
    if (!*p)
        return RET_FALSE;
    if (('-'==*p) || ('+'==*p)) /* for such as "-2.1e+10" or "+2.1e-10" */
        p ++;
    
    SKIP_FLOAT(p, cnt);
    if (!cnt)
        return RET_FALSE;
        
    if ('e' == *p)
    {
        p ++;
        if (('-'==*p) || ('+'==*p))/* for such as "-2.1e+10" or "+2.1e-10" */
            p ++;
        SKIP_INTEGER(p, cnt);
        if (cnt)
            return BLANK_OR_NULL(p);
    }
    else
        return BLANK_OR_NULL(p);
        
    return RET_FALSE;
}
