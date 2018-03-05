#ifndef _DECODER_H_
#define _DECODER_H_

#define code_definition(x , y) y=x

typedef int encoding;

#define code(x , y) const encoding y = x;


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
//-------------------------------------------
//FUNCTIONS

//Single
code(0x0fffff01 , COS);
code(0x0fffff02 , SIN);
code(0x0fffff03 , TG);
code(0x0fffff04 , CTG);
code(0x0fffff05 , SH);
code(0x0fffff06 , CH);
code(0x0fffff07 , TH);
code(0x0fffff08 , CTH);
code(0x0fffff09 , EXP);
code(0x0fffff0a , LN);
code(0x0fffff0b , LG);

//Double
code(0x0fffff0c , ADD);
code(0x0fffff0d , SUB);
code(0x0fffff0e , MUL);
code(0x0fffff0f , DIV);
code(0x0fffff10 , LOG);
code(0x0fffff11 , POW);

//-------------------------------------------
// VARIABLE
code(0x0ffffd01 , a);
code(0x0ffffd02 , b);
code(0x0ffffd03 , c);
code(0x0ffffd04 , d);
code(0x0ffffd05 , e);
code(0x0ffffd06 , f);
code(0x0ffffd07 , g);
code(0x0ffffd08 , h);
code(0x0ffffd09 , i);
code(0x0ffffd0a , j);
code(0x0ffffd0b , k);
code(0x0ffffd0c , l);
code(0x0ffffd0d , m);
code(0x0ffffd0e , n);
code(0x0ffffd0f , o);
code(0x0ffffd10 , p);
code(0x0ffffd11 , q);
code(0x0ffffd12 , r);
code(0x0ffffd13 , s);
code(0x0ffffd14 , t);
code(0x0ffffd15 , u);
code(0x0ffffd16 , v);
code(0x0ffffd17 , w);
code(0x0ffffd18 , x);
code(0x0ffffd19 , y);
code(0x0ffffd1a , z);


/*
 * using in Node (look TreeLib.h)
 * for fast analyze Node
 */
enum  encoding_type
{
    code_definition(0x0ffffff0 , VARIABLE),
    code_definition(0x0ffffff1 , FUNCTION),
    code_definition(0x0ffffff2 , CONSTANT),
};

//===============================================
//Decoder functions

encoding_type ToDefCode   (char* symbol);//Don't realized===============================================================
encoding      ToValueCode (char* symbol);//Don't realized===============================================================




#endif // DECODER_H_

