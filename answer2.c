//#define DEBUG 

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

/* flaot: "0.1" or "0." or ".1" or inter */
static inline char *skip_float(char *p)
{
    char *_p = p;
    if ('.' == *_p) /* for such as ".0" */
    {
        do {
            _p++;
        } while (('0'<=*_p) && ('9'>=*_p));
        if (p+1 == _p)
            _p = p;
    }
    else/* for such as "12." or "12.12" */
    {
        while (('0'<=*_p) && ('9'>=*_p))
            _p++;
        if ((p<_p) && ('.'==*_p))
            do {
                _p++;
            } while (('0'<=*_p) && ('9'>=*_p));
    }
    return _p;
}
    
bool isNumber(char* s) 
{
    char            *p = s;
    char            *p_t = s;
    
    if (!p || (!*p))
        return RET_FALSE;
        
    while (' ' == *p)
        p++;
    if (!*p)
        return RET_FALSE;
    if (('-'==*p) || ('+'==*p)) /* for such as "-2.1e+10" or "+2.1e-10" */
        p++;
        
    p_t = p;
    p = skip_float(p_t);
    if (p_t == p)
        return RET_FALSE;
        
    if ('e' == *p)
    {
        p++;
        if (('-'==*p) || ('+'==*p))/* for such as "-2.1e+10" or "+2.1e-10" */
            p++;
        p_t = p;
        while (('0'<=*p) && ('9'>=*p))
            p++;
        if (p_t != p)
        {
            while (' ' == *p)   /* skip blank */
                p++;
            return (*p)?(RET_FALSE):(RET_TRUE);
        }
    }
    else
    {
        while (' ' == *p)   /* skip blank */
            p++;
        return (*p)?(RET_FALSE):(RET_TRUE);
    }
        
    return RET_FALSE;
}
