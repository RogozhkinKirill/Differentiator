#ifndef _DECODER_H_
#define _DECODER_H_

#define code(x , y) y=x

/**============================================================================
  * using in Node (look TreeLib.h)
  * for fast analyze Node
  *
  * Functions could be:
  *                    1)Single (1 argument ex. cos(x))
  *
  *                                Enumeration:
  *                         cos(x), sin(x), tg(x), ctg(x),
  *                         sh(x),  ch(x),  th(x), cth(x),
  *                         -x,     exp(x), ln(x), lg(x),
  *
  *
  *                          Save Argument to LEFT  Node
  *                               NULL     to RIGHT Node
  *
  *                                 It looks like
  *
  *                                   ----------
  *                                   |Function|
  *                                   ----------
  *                                  /          \
  *                                 /            \
  *                          ------------       ------
  *                          |Argument(x)|      |NULL|
  *                          ------------       ------
  *
  *
  *
  *                    2)Double (2 argument ex. x+y)
  *
  *                                  Enumeration:
  *                          x+y,    x-y,    x*y,   x/y,
  *                     log(x,y) (x - base,     y - argument),
  *                       x^y    (x - argument, y - power),
  *
  *
  *
  *                          Save 1 Argument to LEFT  Node
  *                               2 Argument to RIGHT Node
  *
  *                                 It looks like
  *
  *                                   ----------
  *                                   |Function|
  *                                   ----------
  *                                  /          \
  *                                 /            \
  *                                /              \
  *                        ---------------    ---------------
  *                        |1 Argument(x)|    |2 Argument(y)|
  *                        ---------------    ---------------
  *
  *============================================================================
  */
enum encoding
{
    //-------------------------------------------
    //FUNCTIONS

    //Single
    code(0x0fffff01 , cos),
    code(0x0fffff02 , sin),
    code(0x0fffff03 , tg),//Don't realized
    code(0x0fffff04 , ctg),//Don't realized
    code(0x0fffff05 , sh),
    code(0x0fffff06 , ch),
    code(0x0fffff07 , th),//Don't realized
    code(0x0fffff08 , cth),//Don't realized
    code(0x0fffff09 , exp),
    code(0x0fffff0a , ln),
    code(0x0fffff0b , lg),

    //Double
    code(0x0fffff0c , add),
    code(0x0fffff0d , sub),
    code(0x0fffff0e , mul),
    code(0x0fffff0f , div),
    code(0x0fffff10 , log),
    code(0x0fffff11 , pow),
    code(0x0fffff12 , minus),

    //-------------------------------------------
    // VARIABLE
    code(0x0ffffd01 , a),
    code(0x0ffffd02 , b),
    code(0x0ffffd03 , c),
    code(0x0ffffd04 , d),
    code(0x0ffffd05 , e),
    code(0x0ffffd06 , f),
    code(0x0ffffd07 , g),
    code(0x0ffffd08 , h),
    code(0x0ffffd09 , i),
    code(0x0ffffd0a , j),
    code(0x0ffffd0b , k),
    code(0x0ffffd0c , l),
    code(0x0ffffd0d , m),
    code(0x0ffffd0e , n),
    code(0x0ffffd0f , o),
    code(0x0ffffd10 , p),
    code(0x0ffffd11 , q),
    code(0x0ffffd12 , r),
    code(0x0ffffd13 , s),
    code(0x0ffffd14 , t),
    code(0x0ffffd15 , u),
    code(0x0ffffd16 , v),
    code(0x0ffffd17 , w),
    code(0x0ffffd18 , x),
    code(0x0ffffd19 , y),
    code(0x0ffffd1a , z),
};


/*
 * using in Node (look TreeLib.h)
 * for fast analyze Node
 */
enum  encoding_type
{
    code(0x0ffffff0 , VARIABLE),
    code(0x0ffffff1 , FUNCTION),
    code(0x0ffffff2 , CONSTANT),
};

//===============================================
//Decoder functions

encoding_type ToDefCode   (char* symbol);//Don't realized===============================================================
encoding      ToValueCode (char* symbol);//Don't realized===============================================================

char* ToStrFromCode (encoding_type define , encoding value);//Don't realized============================================



#endif // DECODER_H_

